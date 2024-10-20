/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/20 19:05:02 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_things(t_pip *struc, char **env, char **argv, int argc)
{
	struc->argv = argv;
	struc->env = env;
	struc->exit_status = 0;
	struc->pids = NULL;
	struc->cmd_args = NULL;
	struc->cmd_path = NULL;
	if (struc->here_doc >= 0)
	{
		struc->nb_cmds = argc - 4;
		struc->nb_pipes = struc->nb_cmds - 1;
	}
	else
	{
		struc->nb_cmds = argc - 3;
		struc->nb_pipes = struc->nb_cmds - 1;
	}
	struc->pids = (pid_t *)malloc(sizeof(pid_t) * struc->nb_cmds);
	if (!struc->pids)
	{
		struc->pids = NULL;
		handle_error("malloc failed", struc, 0);
	}
	init_pipes(struc);
}

void	init_pipes(t_pip *struc)
{
	int	i;

	struc->pipes = malloc(sizeof(int *) * struc->nb_pipes);
	if (!struc->pipes)
	{
		struc->pipes = NULL;
		handle_error("malloc failed", struc, 0);
	}
	i = 0;
	while (i < struc->nb_pipes)
	{
		struc->pipes[i] = malloc(sizeof(int) * 2);
		if (!struc->pipes[i])
		{
			struc->pipes[i] = NULL;
			handle_error("malloc failed", struc, 0);
		}
		if (pipe(struc->pipes[i]) == -1)
			handle_error("pipe creation failed", struc, 0);
		i++;
	}
}

void	parse_args(char **argv, int argc, t_pip *struc)
{
	int	i;

	i = 0;
	if (!find_count_exe(argv, argc, struc))
	{
		ft_putstr_fd("Wrong number of args\n", 2);
		exit(EXIT_FAILURE);
	}
	while (argv[i])
	{
		if (!argv[i] || only_space(argv[i]) || argv[i][0] == '\0')
		{
			ft_putstr_fd("Arg empty\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	wait_for_children(t_pip *struc)
{
	int	i;
	int	status;

	i = 0;
	while (i < struc->nb_cmds)
	{
		waitpid(struc->pids[i], &status, 0);
		if (WIFEXITED(status))
			struc->exit_status = WEXITSTATUS(status);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	struc;
	int		i;

	parse_args(argv, argc, &struc);
	init_things(&struc, env, argv, argc);
	open_fd_in(&struc);
	i = 0;
	while (i < struc.nb_cmds)
	{
		struc.pids[i] = handle_child(&struc, i);
		i++;
	}
	close_all_pipes(&struc);
	wait_for_children(&struc);
	if (struc.here_doc == -2 || struc.here_doc >= 0)
		unlink("here_doc");
	free(struc.pids);
	free_pipes(&struc);
	return (struc.exit_status);
}
