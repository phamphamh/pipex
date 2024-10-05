/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/05 22:36:50 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  < file1 cmd1 | cmd2 > file2
// recu en arg = file1 cmd1 cmd2 file2

void	init_things(t_pip *struc, char **env, char **argv, int argc)
{
	struc->argv = argv;
	struc->env = env;
	struc->exit_status = 0;
	if (struc->here_doc >= 0)
		struc->nb_cmds = argc - 4;
	else
		struc->nb_cmds = argc - 3;
	init_pipes(struc);
}

void	init_pipes(t_pip *struc)
{
	int	i;
	struc->nb_pipes = struc->nb_cmds - 1;
	struc->pipes = malloc(sizeof(int *) * struc->nb_pipes);
	if (!struc->pipes)
		handle_error("malloc failed");
	i = 0;
	while (i < struc->nb_pipes)
	{
		struc->pipes[i] = malloc(sizeof(int) * 2);
		if (!struc->pipes[i])
			handle_error("malloc failed");
		if (pipe(struc->pipes[i]) == -1)
			handle_error("pipe creation failed");
		i++;
	}
}

void	parse_args(char **argv, int argc, t_pip *struc)
{
	int	i;

	i = 0;
	if (!find_count_exe(argv, argc, struc))
		handle_error("usage: ./pipex file1 cmd1 cmd2 file2");
	while (argv[i])
	{
		if (!argv[i] || only_space(argv[i]) || argv[i][0] == '\0')
			handle_error("Arg empty");
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pip	struc;
	int		i;
	int		status;
	int		child_status;

	ft_memset(&struc, 0, sizeof(t_pip)); // pas sur
	parse_args(argv, argc, &struc);
	init_things(&struc, env, argv, argc);
	struc.pids = (pid_t *)malloc(sizeof(pid_t) * struc.nb_cmds);
	i = 0;
	while (i < struc.nb_cmds)
	{
		struc.pids[i] = handle_child(&struc, i);
		i++;
	}
	i = 0;
	while (i < struc.nb_pipes)
	{
		close(struc.pipes[i][0]);
		close(struc.pipes[i][1]);
		i++;
	}
	i = 0;
	child_status = 0;
	while (i < struc.nb_cmds)
	{
		waitpid(struc.pids[i], &status, 0);
		if (WIFEXITED(status))
		{
			// verifier l argument de err cmd et wexit status, pour avoir file1 command
			// not found quand  ./pipex here_doc lim file1 cat cat cat file2
			child_status = WEXITSTATUS(status);
			if (child_status != 0)
			{
				ft_putstr_fd(struc.err_cmd, STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
			}
		}
		i++;
	}
	free(struc.pids);
	free_pipes(&struc);
	return (0);
}
