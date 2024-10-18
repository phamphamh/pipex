/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:01:08 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/18 07:59:46 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_fd_in(t_pip *struc)
{
	if (struc->here_doc >= 0)
	{
		struc->fd = open("here_doc", O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (struc->fd < 0)
			handle_error("", struc, 0);
		set_here_doc(struc);
		struc->here_doc = -2;
	}
	else
		struc->fd = open(struc->argv[struc->exec_pos + 1], O_RDONLY);
	if (struc->fd < 0)
	{
		ft_putstr_fd(struc->argv[struc->exec_pos + 1], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
	}
}

void	open_fd_out(t_pip *struc)
{
	int	i;

	i = ft_strllen(struc->argv);
	if (struc->here_doc == -2)
		struc->fd = open(struc->argv[i - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		struc->fd = open(struc->argv[i - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (struc->fd < 0)
		handle_error("", struc, 0);
}
