/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:01:08 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:24:46 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

void	open_fd_in(t_pip *struc)
{
	if (struc->here_doc == -2)
	{
		struc->fd = open("here_doc", O_RDONLY);
		if (struc->fd == -1)
			ft_putstr_fd
			("here_doc : no such file or directory or acces unauthorized\n", 2);
	}
	else
	{
		struc->fd = open(struc->argv[struc->exec_pos + 1], O_RDONLY);
		if (struc->fd == -1)
			ft_putstr_fd
			("infile : no such file or directory or acces unauthorized\n", 2);
	}
}

void	open_fd_out(t_pip *struc)
{
	int	i;

	i = ft_strllen(struc->argv);
	if (struc->here_doc == -2 || struc->here_doc >= 0)
		struc->fd = open(struc->argv[i - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		struc->fd = open(struc->argv[i - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (struc->fd == -1)
		ft_putstr_fd
		("outfile : no such file or directory or acces unauthorized\n", 2);
}
