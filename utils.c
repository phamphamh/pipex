/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:09:03 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/17 17:52:57 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strllen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp_env(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] == '\n')
		return (s1[i] - '\n');
	return (0);
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

bool	only_space(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

void	handle_error(char *message, t_pip *struc, int nb_error)
{
	if (struc->pipes)
	{
		close_all_pipes(struc);
		free_pipes(struc);
	}
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
	if (struc->here_doc == -2 || struc->here_doc >= 0)
	{
		struc->here_doc = -1;
		unlink("here_doc");
	}
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

int	ft_strcmp_trimmed(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len2 > 0 && s2[len2 - 1] == '\n')
		len2--;
	if (len1 != len2)
		return (1);
	return (ft_strncmp(s1, s2, len1));
}
/*
void	ft_close(int *fd)
{
	if (*fd == 1 || *fd == 0 || *fd == 2 || *fd == -1)
		return ;
	else
		close (*fd);
	*fd = -1;
}
*/

void free_pipes(t_pip *struc)
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
