/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/08 02:40:55 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve_1(char *cmd_path, char **args, t_pip *struc, int fd)
{
		close(struc->pipe_tab[0]);
		if (dup2(fd, STDIN_FILENO) == -1 || dup2(struc->pipe_tab[1], STDOUT_FILENO) == -1)
			handle_error("dup2");
		close(fd);
		close(struc->pipe_tab[1]);
		execve(cmd_path, args, struc->env); // verifier utilite des arg 1 et 3
		perror("execve");
		exit(EXIT_FAILURE);
}

pid_t	handle_child_1(t_pip *struc)
{
	int		fd;
	pid_t	pid;
	char 	**args;
	char	*cmd_path;

	fd = open(struc->argv[1], O_RDONLY);
	if (fd == -1)
		handle_error("open");
	pid = fork();
	if (pid == -1)
		handle_error("fork");
	args = ft_split(struc->argv[2], ' ');
	cmd_path = check_path(args[0], struc->env);
	if (!cmd_path)
	handle_error("cmd_path");
	if (pid == 0)
		ft_execve_1(cmd_path, args, struc, fd);
	free(cmd_path);
	free_all(args);
	return (pid);
}

void	ft_execve_2(char *cmd_path, char **args, t_pip *struc, int fd)
{
		close(struc->pipe_tab[1]);
		if (dup2(fd, STDOUT_FILENO) == -1 || dup2(struc->pipe_tab[0], STDIN_FILENO) == -1)
			handle_error("dup2");
		close(fd);
		close(struc->pipe_tab[0]);
		execve(cmd_path, args, struc->env); // verifier utilite des arg 1 et 3
		perror("execve");
		exit(EXIT_FAILURE);
}

pid_t	handle_child_2(t_pip *struc)
{
	int		fd;
	pid_t	pid;
	char 	**args;
	char	*cmd_path;

	fd = open(struc->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		handle_error("open");
	pid = fork();
	if (pid == -1)
		handle_error("fork");
	args = ft_split(struc->argv[3], ' ');
	cmd_path = check_path(args[0], struc->env);
	if (!cmd_path)
		handle_error("cmd_path");
	if (pid == 0)
		ft_execve_2(cmd_path, args, struc, fd);
	free(cmd_path);
	free_all(args);
	return (pid);
}
