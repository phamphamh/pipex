/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/20 21:29:17 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_here_doc(t_pip *struc)
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
		write(struc->fd, line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	close(struc->fd);
	struc->fd = open("here_doc", O_RDONLY);
	if (struc->fd < 0)
		handle_error("", struc, 0);
}

void	set_cmd_args(t_pip *struc, int idx)
{
	int	i;

	if (struc->here_doc == -2 || struc->here_doc >= 0)
		i = idx + struc->exec_pos + 3;
	else
		i = idx + struc->exec_pos + 2;
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
		handle_error(" : command not found", struc, 0);
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

void	dup_child(t_pip *struc, int idx)
{
	if (idx == 0)
	{
		dup2(struc->fd, STDIN_FILENO);
		if (struc->fd != -1)
			close(struc->fd);
		dup2(struc->pipes[0][1], STDOUT_FILENO);
	}
	else if (idx == struc->nb_cmds - 1)
	{
		open_fd_out(struc);
		dup2(struc->pipes[idx - 1][0], STDIN_FILENO);
		dup2(struc->fd, STDOUT_FILENO);
		close(struc->fd);
	}
	else
	{
		dup2(struc->pipes[idx - 1][0], STDIN_FILENO);
		dup2(struc->pipes[idx][1], STDOUT_FILENO);
	}
}

pid_t	handle_child(t_pip *struc, int idx)
{
	pid_t	pid;

	set_cmd_args(struc, idx);
	pid = fork();
	if (pid == -1)
		handle_error("fork failed", struc, 0);
	if (pid == 0)
	{
		dup_child(struc, idx);
		close_all_pipes(struc);
		ft_execve(struc);
	}
	else
		free_parent(struc, idx);
	return (pid);
}
