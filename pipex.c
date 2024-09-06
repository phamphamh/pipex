/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 19:28:05 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/06 19:31:53 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//  < file1 cmd1 | cmd2 > file2
// recu en arg = file1 cmd1 cmd2 file2

pid_t	handle_child_1(char	*file, char	*cmd, int *pipe_tab)
{
	int		fd;
	pid_t	pid;
	char 	**args;

	fd = open(file, O_RDONLY);
	{
		perror("open");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	// verifier aussi si tous les arguments sont bons
	args = ft_split(cmd, ' ');
	if (pid == 0)
	{
		close(pipe_tab[0]);
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (dup2(pipe_tab[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
		close(pipe_tab[1]);
		execve("/bin/", args, NULL); // verifier utilite des arg 1 et 3
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

pid_t	handle_child_2(char	*file, char	*cmd, int *pipe_tab)
{
	int		fd;
	pid_t	pid;
	char 	**args;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC);
	{
		perror("open");
		exit (EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit (EXIT_FAILURE);
	}
	// verifier aussi si tous les arguments sont bons
	args = ft_split(cmd, ' ');
	if (pid == 0)
	{
		close(pipe_tab[1]);
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (dup2(pipe_tab[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd);
		close(pipe_tab[0]);
		execve("/bin/", args, NULL); // verifier utilite des arg 1 et 3
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_tab[2];
	int		pipe_ret;

	pipe_ret = pipe(pipe_tab);
	if (pipe_ret == -1)
	{
		perror("pipe");
		exit (EXIT_FAILURE);
	}
	pid1 = handle_child_1(argv[1], argv[2], pipe_tab);
	pid2 = handle_child_2(argv[4], argv[3], pipe_tab);
	close(pipe_tab[0]);
	close(pipe_tab[1]);
	if (pid1 > 0 && pid2 > 0)
	{
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}
