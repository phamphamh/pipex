/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:00:39 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:24:55 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

void	free_parent(t_pip *struc)
{
	if (struc->idx > 0)
		close(struc->pipes[struc->idx - 1][0]);
	if (struc->idx < struc->nb_cmds - 1)
		close(struc->pipes[struc->idx][1]);
	if (struc->cmd_args)
	{
		free_all(struc->cmd_args);
		struc->cmd_args = NULL;
	}
	if (struc->cmd_path)
	{
		free(struc->cmd_path);
		struc->cmd_path = NULL;
	}
}

void	free_all(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_pipes(t_pip *struc)
{
	int	i;

	i = 0;
	while (i < struc->nb_pipes)
	{
		free(struc->pipes[i]);
		i++;
	}
	free(struc->pipes);
	struc->pipes = NULL;
}

void	return_message(char *message, int nb_error)
{
	if (message && message[0] != '\0')
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	if (nb_error == 0)
		nb_error = 1;
	if (nb_error != -1)
		exit(nb_error);
}

void	handle_error(char *message, t_pip *struc, int nb_error)
{
	if (struc->pipes)
	{
		close_all_pipes(struc);
		free_pipes(struc);
	}
	if (struc->fd && struc->fd != -2 && struc->fd != -1)
		close(struc->fd);
	if (struc->cmd_path)
	{
		free(struc->cmd_path);
		struc->cmd_path = NULL;
	}
	if (struc->cmd_args)
	{
		free_all(struc->cmd_args);
		struc->cmd_args = NULL;
	}
	if (struc->pids)
		free(struc->pids);
	if (struc->here_doc == -2)
	{
		struc->here_doc = -1;
		unlink("here_doc");
	}
	return_message(message, nb_error);
}
