/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/17 17:15:14 by yboumanz         ###   ########.fr       */
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

	parse_args(argv, argc, &struc);
	init_things(&struc, env, argv);
	while (struc.pids)
		struc.pids = handle_child(&struc);
	close(struc.pipe_tab[0]);
	close(struc.pipe_tab[1]);
	if (struc.pids[0] > 0 && struc.pids[1] > 0)
	{
		waitpid(struc.pids[0], NULL, 0);
		waitpid(struc.pids[1], NULL, 0);
	}
	return (0);
}
