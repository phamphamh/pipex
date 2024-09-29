/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 02:40:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/29 21:43:54 by yboumanz         ###   ########.fr       */
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
}

void	set_cmd_args(t_pip *struc, int idx)
{
	int	i;

	if (struc->here_doc == -2)
	{
		printf("yo\n");
		i = idx + struc->exec_pos + 3;
	}
	else
		i = idx + struc->exec_pos + 2;
	struc->cmd_args = ft_split(struc->argv[i], ' ');
	if (struc->cmd_args[0][0] == '/')
		struc->cmd_path = ft_strdup(struc->cmd_args[0]);
	else
		struc->cmd_path = check_path(struc->cmd_args[0], struc->env);
}

void	ft_execve(t_pip *struc)
{
		execve(struc->cmd_path, struc->cmd_args, struc->env);
		ft_putstr_fd(struc->cmd_args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
}

pid_t	handle_child(t_pip *struc)
{
	pid_t	pid;
	int		i;

	i = 0;
	open_fd_in(struc);
	while (i < struc->nb_cmds)
	{
		if (i != struc->nb_cmds - 1)
			pipe(struc->pipe_fds);
		pid = fork();
		if (pid == -1)
			handle_error("fork");
		if (pid == 0)
		{
			if (i == 0)
				handle_first_cmd(struc);
			else if (i == struc->nb_cmds - 1)
			{
				handle_last_cmd(struc);
			}
			else
			{
				handle_mid_cmd(struc);
			}
			set_cmd_args(struc, i);
			ft_execve(struc);
		}
		else
		{
			if (i > 0)
				close(struc->pipe_tab[0]);
			if (i < struc->nb_cmds - 1)
			{
				close(struc->pipe_fds[1]);
				struc->pipe_tab[0] = struc->pipe_fds[0];
			}
		}
		i++;
	}
	return (pid);
}
