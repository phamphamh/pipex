/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/20 13:07:53 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  < file1 cmd1 | cmd2 > file2
// recu en arg = file1 cmd1 cmd2 file2

void	init_things(t_pip *struc, char **env, char **argv, int argc)
{
	struc->argv = argv;
	struc->env = env;
	if (struc->here_doc >= 0)
		struc->nb_cmds = argc - 4;
	else
		struc->nb_cmds = argc - 3;
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

	parse_args(argv, argc, &struc);
	init_things(&struc, env, argv, argc);
	struc.pids = (pid_t *)malloc(sizeof(pid_t) * struc.nb_cmds);
	i = 0;
	while (i < struc.nb_cmds)
	{
		struc.pids[i] = handle_child(&struc);
		if (i > 0)
			close(struc.pipe_tab[0]);
		if (i < struc.nb_cmds - 1)
			close(struc.pipe_tab[1]);
		if (i < struc.nb_cmds - 1)
			struc.pipe_tab[0] = struc.pipe_fds[0];
		i++;
	}
	while (i > 0)
	{
		waitpid(struc.pids[i], NULL, 0);
		i--;
	}
	free(struc.pids);
	return (0);
}
