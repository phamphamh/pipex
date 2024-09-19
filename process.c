/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/19 14:06:07 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_execve_1(char *cmd_path, char **args, t_pip *struc, int fd)
{
		// j peux pas close fd, jss dans une 
		close(struc->pipe_tab[0]);
		if (dup2(fd, STDIN_FILENO) == -1 || dup2(struc->pipe_tab[1], STDOUT_FILENO) == -1)
			handle_error("dup2");
		close(fd);
		close(struc->pipe_tab[1]);
		execve(cmd_path, args, struc->env);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
}

void	ft_execve_2(char *cmd_path, char **args, t_pip *struc, int fd)
{
		close(struc->pipe_tab[1]);
		if (dup2(fd, STDOUT_FILENO) == -1 || dup2(struc->pipe_tab[0], STDIN_FILENO) == -1)
			handle_error("dup2");
		close(fd);
		close(struc->pipe_tab[0]);
		execve(cmd_path, args, struc->env);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
}

void	set_here_doc(t_pip *struc)
{
	char	*limiter;
	char	*line;

	limiter = ft_strdup(struc->argv[struc->here_doc + 1]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strcmp(line, limiter))
			break ;
		write (struc->fd, line, ft_strlen(line));
		write (struc->fd, "\n", 1);
		free(line);
	}
}

void	open_files(t_pip *struc, int idx)
{
	if (struc->here_doc >= 0)
	{
		struc->fd = open("here_doc", O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (struc->fd == -1)
				handle_error("open");
		set_here_doc(struc);
		struc->here_doc = -2;
		idx++;
	}
	else if (idx++ == (struc->exec_pos + 1))
		struc->fd = open(struc->argv[idx], O_RDONLY);
	else if (struc->argv[idx] == (ft_strllen(struc->argv) - 1))
	{
			if (struc->here_doc == -2)
				struc->fd = open(struc->argv[idx] ,O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				struc->fd = open(struc->argv[idx], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (struc->fd == -1)
		handle_error("open");
}

void	set_cmd_args(t_pip *struc, int idx)
{
	struc->cmd_args = ft_split(struc->argv[idx], ' ');
	if (struc->cmd_args[0][0] == '/')
		struc->cmd_path = ft_strdup(struc->cmd_args[0]);
	else
		struc->cmd_path = check_path(struc->cmd_args[0], struc->env);
}

pid_t	handle_child(t_pip *struc)
{
	pid_t	pid;
	char 	**args = NULL;
	char	*cmd_path = NULL;
	int		i;
	int		fd;

	i = 0;
	pid = fork();
	if (pid == -1)
		handle_error("fork");
	while (i < ft_strllen(struc->argv - 3))
	{
		if (i != )
		pid = pipe(struc->pipe_fds);
		if (pid == 0)
		{
			open_files(struc, i);
			set_cmd_args(struc, i);
			ft_execve_1(cmd_path, args, struc, fd);
		}
		i++;
	}
	if (cmd_path)
		free(cmd_path);
	if (args)
		free_all(args);
	return (pid);
}


pid_t	handle_child_2(t_pip *struc)
{
	int		fd;
	pid_t	pid;
	char 	**args = NULL;
	char	*cmd_path = NULL;

	pid = fork();
	if (pid == -1)
		handle_error("fork");
	if (pid == 0)
	{
		if (struc->here_doc >= 0)
			fd = open(struc->argv[4] ,O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(struc->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			handle_error("open");
		args = ft_split(struc->argv[3], ' ');
		if (args[0][0] == '/')
			cmd_path = ft_strdup(args[0]);
		else
		{
			cmd_path = check_path(args[0], struc->env);
		}
		//if (!cmd_path && cmd_path[0] != 0)
		//	handle_error("cmd_path");
		ft_execve_2(cmd_path, args, struc, fd);
	}
	if (cmd_path)
		free(cmd_path);
	if (args)
		free_all(args);
	return (pid);
}
