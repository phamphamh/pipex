/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/11 21:29:22 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
int fd[2];
pipe(fd);
while (1)
{
	write(fd[1], line, strlen(line));
	write(fd[1], "\n", 1);
}
close(fd[1]);
return (fd[0]);
*/

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
		//write(struc->pipes[0][0], line, ft_strlen(line));
		free(line);
	}
	free(limiter);
	struc->fd = open("here_doc", O_RDONLY);
	if (struc->fd < 0)
		handle_error("open here_doc for reading", struc, 0);
}

void	set_cmd_args(t_pip *struc, int idx)
{
	int	i;

	if (struc->here_doc == -2)
	{
		i = idx + struc->exec_pos + 3;
	}
	else
		i = idx + struc->exec_pos + 2;
	struc->cmd_args = ft_split(struc->argv[i], ' ');
	if (!struc->cmd_args || !struc->cmd_args[0])
	{
		ft_putstr_fd("Error: Invalid command\n", 2);
		handle_error("", struc, 0);
    }
	if (struc->cmd_args[0][0] == '/')
		struc->cmd_path = ft_strdup(struc->cmd_args[0]);
	else
		struc->cmd_path = check_path(struc->cmd_args[0], struc->env);
	if (!struc->cmd_path)
	{
		ft_putstr_fd(struc->cmd_args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		handle_error("", struc, 0);
	}
}

void	ft_execve(t_pip *struc)
{
	    if (!struc->cmd_path || access(struc->cmd_path, F_OK) == -1)
    {
        ft_putstr_fd(struc->cmd_args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    else if (access(struc->cmd_path, X_OK) == -1)
    {
        ft_putstr_fd(struc->cmd_args[0], 2);
        ft_putstr_fd(": Permission denied\n", 2);
        exit(126);
    }
	/*
	if (!struc->cmd_path || access(struc->cmd_path, F_OK) == -1)
		handle_error("command not found\n", struc, 127);
	else if (access(struc->cmd_path, X_OK) == -1)
		handle_error("Permission denied\n", struc, 126);
	*/
	execve(struc->cmd_path, struc->cmd_args, struc->env);
	perror(struc->cmd_args[0]);
	exit(EXIT_FAILURE);
}

pid_t	handle_child(t_pip *struc, int idx)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == -1)
		handle_error("fork", struc, 0);
	if (pid == 0)
	{
		if (idx == 0)
		{
			open_fd_in(struc);
			dup2(struc->fd, STDIN_FILENO);
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
		while (i < struc->nb_pipes)
		{
			close(struc->pipes[i][0]);
            close(struc->pipes[i][1]);
            i++;
			/*
			if (i != idx - 1)
				close(struc->pipes[i][0]);
			if (i != idx)
				close(struc->pipes[i][1]);
			i++;
			*/
		}
		set_cmd_args(struc, idx);
		ft_execve(struc);
	}
	else
	{
		if (idx > 0)
			close(struc->pipes[idx-1][0]);
		if (idx < struc->nb_cmds - 1)
			close(struc->pipes[idx][1]);
	}
	return (pid);
}
