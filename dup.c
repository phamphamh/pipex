/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:01:08 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/30 01:07:32 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
