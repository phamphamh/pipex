/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/08 03:40:05 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  < file1 cmd1 | cmd2 > file2
// recu en arg = file1 cmd1 cmd2 file2

void	init_things(t_pip *struc, char **env, char **argv)
{
	int	pipe_return;

	struc->argv = argv;
	struc->env = env;
	pipe_return = pipe(struc->pipe_tab);
	if (pipe_return == -1)
	{
		perror("pipe");
		exit (EXIT_FAILURE);
	}
}
int	main(int argc, char **argv, char **env)
{
	t_pip	struc;

	if (argc < 5)
		handle_error("usage: ./pipex file1 cmd1 cmd2 file2");
	init_things(&struc, env, argv);
	struc.pids[0] = handle_child_1(&struc);
	struc.pids[1] = handle_child_2(&struc);
	close(struc.pipe_tab[0]);
	close(struc.pipe_tab[1]);
	if (struc.pids[0] > 0 && struc.pids[1] > 0)
	{
		waitpid(struc.pids[0], NULL, 0);
		waitpid(struc.pids[1], NULL, 0);
	}
	return (0);
}
