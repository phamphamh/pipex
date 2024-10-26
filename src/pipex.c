/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:25:41 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	init_things(t_pip *struc, char **env, char **argv, int argc)
{
	int	temp_fd;

	temp_fd = -2;
	struc->idx = 0;
	struc->argv = argv;
	struc->env = env;
	struc->exit_status = 0;
	struc->pids = NULL;
	struc->cmd_args = NULL;
	struc->cmd_path = NULL;
	struc->pipes = NULL;
	struc->fd = -2;
	struc->argc = argc;
	if (struc->here_doc >= 0)
	{
		temp_fd = open("here_doc", O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (temp_fd == -1)
			unlink("here_doc");
		else
		{
			set_here_doc(struc, temp_fd);
			struc->here_doc = -2;
		}
	}
	init_pipes(struc);
}

void	init_pipes(t_pip *struc)
{
	int	i;

	struc->pids = (pid_t *)malloc(sizeof(pid_t) * struc->nb_cmds);
	if (!struc->pids)
	{
		struc->pids = NULL;
		handle_error("malloc failed", struc, 0);
	}
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
		if (!struc->pipes[i] || pipe(struc->pipes[i]) == -1)
		{
			struc->pipes[i] = NULL;
			handle_error("malloc or pipe creation failed", struc, 0);
		}
		i++;
	}
}

void	parse_args(char **argv, int argc, t_pip *struc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Wrong number of args\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!ft_strcmp_trimmed("here_doc", argv[1]))
	{
		ft_putstr_fd("here doc not authorized\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!find_count_exe(argv, argc, struc))
	{
		ft_putstr_fd("Wrong number of args\n", 2);
		exit(EXIT_FAILURE);
	}
	struc->nb_cmds = argc - 3;
	struc->nb_pipes = struc->nb_cmds - 1;
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
	i = 0;
	while (struc.idx < struc.nb_cmds)
	{
		struc.pids[struc.idx] = handle_child(&struc);
		struc.idx++;
	}
	close_all_pipes(&struc);
	wait_for_children(&struc);
	if (struc.here_doc == -2 || struc.here_doc >= 0)
		unlink("here_doc");
	free(struc.pids);
	free_pipes(&struc);
	return (struc.exit_status);
}
