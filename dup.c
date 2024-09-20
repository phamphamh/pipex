/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:01:08 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/20 13:21:58 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_first_cmd(t_pip *struc)
{
	dup2(struc->fd, STDIN_FILENO);
	close(struc->fd);
	dup2(struc->pipe_fds[1], STDOUT_FILENO);
	close(struc->pipe_fds[0]);
	close(struc->pipe_fds[1]);
}

void	handle_last_cmd(t_pip *struc)
{
	open_fd_out(struc);
	dup2(struc->pipe_tab[0], STDIN_FILENO);
	close(struc->pipe_tab[0]);
	dup2(struc->fd, STDOUT_FILENO);
	close(struc->fd);
}

void	handle_mid_cmd(t_pip *struc)
{
	dup2(struc->pipe_tab[0], STDIN_FILENO);
	dup2(struc->pipe_fds[1], STDOUT_FILENO);
	close(struc->pipe_tab[0]);
	close(struc->pipe_fds[1]);
}

void	open_fd_in(t_pip *struc)
{
	if (struc->here_doc >= 0)
	{
		struc->fd = open("here_doc", O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (struc->fd == -1)
				handle_error("open");
		set_here_doc(struc);
		struc->here_doc = -2;
	}
	else
		struc->fd = open(struc->argv[struc->exec_pos + 1], O_RDONLY);
	if (struc->fd < 0)
		handle_error("open");
}

void	open_fd_out(t_pip *struc)
{
	int	i;

	i = ft_strllen(struc->argv);
	if (struc->here_doc == -2)
		struc->fd = open(struc->argv[i - 1] ,O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		struc->fd = open(struc->argv[i - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (struc->fd < 0)
		handle_error("open");
}
