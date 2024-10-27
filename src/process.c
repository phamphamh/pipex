/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/27 14:35:59 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	set_here_doc(t_pip *struc, int temp_fd)
{
	char	*limiter;
	char	*line;

	limiter = ft_strdup(struc->argv[struc->here_doc + 1]);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		if (!line)
			break ;
		if (ft_strcmp_trimmed(limiter, line) == 0)
		{
			free(line);
			break ;
		}
		write(temp_fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	close(temp_fd);
}

void	set_cmd_args(t_pip *struc)
{
	int	i;

	if (struc->here_doc == -2 || struc->here_doc >= 0)
		i = struc->idx + struc->exec_pos + 3;
	else
		i = struc->idx + struc->exec_pos + 2;
	if (!struc->argv[i] || only_space(struc->argv[i])
		|| struc->argv[i][0] == '\0')
		return ;
	if (struc->cmd_args)
		free_all(struc->cmd_args);
	struc->cmd_args = ft_split(struc->argv[i], ' ');
	if (struc->cmd_path)
		free(struc->cmd_path);
	if (struc->cmd_args[0][0] == '/')
		struc->cmd_path = ft_strdup(struc->cmd_args[0]);
	else
		struc->cmd_path = check_path(struc->cmd_args[0], struc->env);
}

void	ft_execve(t_pip *struc)
{
	if (!struc->cmd_args)
		handle_error("Command empty", struc, 0);
	if (!struc->cmd_path)
	{
		ft_putstr_fd(struc->cmd_args[0], 2);
		handle_error(" : command not found", struc, 127);
	}
	else if (access(struc->cmd_path, F_OK) == -1)
	{
		ft_putstr_fd(struc->cmd_args[0], 2);
		handle_error(" : command not found", struc, 127);
	}
	else if (access(struc->cmd_path, X_OK) == -1)
	{
		ft_putstr_fd(struc->cmd_args[0], 2);
		handle_error(" : permission denied", struc, 126);
	}
	execve(struc->cmd_path, struc->cmd_args, struc->env);
	exit(EXIT_FAILURE);
}

void	dup_child(t_pip *struc)
{
	if (struc->idx == 0)
	{
		open_fd_in(struc);
		if (dup2(struc->fd, STDIN_FILENO) == -1)
			handle_error("dup2 infile error", struc, 0);
		if (struc->fd && struc->fd != -2 && struc->fd != -1)
			close(struc->fd);
		dup2(struc->pipes[0][1], STDOUT_FILENO);
	}
	else if (struc->idx == struc->nb_cmds - 1)
	{
		open_fd_out(struc);
		dup2(struc->pipes[struc->idx - 1][0], STDIN_FILENO);
		if (dup2(struc->fd, STDOUT_FILENO) == -1)
			handle_error("dup2 outfile error", struc, 0);
		if (struc->fd && struc->fd != -2 && struc->fd != -1)
			close(struc->fd);
	}
	else
	{
		dup2(struc->pipes[struc->idx - 1][0], STDIN_FILENO);
		dup2(struc->pipes[struc->idx][1], STDOUT_FILENO);
	}
}

pid_t	handle_child(t_pip *struc)
{
	pid_t	pid;

	set_cmd_args(struc);
	pid = fork();
	if (pid == -1)
		handle_error("fork failed", struc, 0);
	if (pid == 0)
	{
		dup_child(struc);
		close_all_pipes(struc);
		ft_execve(struc);
	}
	else
		free_parent(struc);
	return (pid);
}
