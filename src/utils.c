/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:09:03 by yboumanz          #+#    #+#             */
/*   Updated: 2024/10/26 23:25:48 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

bool	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
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

void	close_all_pipes(t_pip *struc)
{
	int	i;

	i = 0;
	while (i < struc->nb_pipes)
	{
		if (struc->pipes[i])
		{
			close(struc->pipes[i][1]);
			close(struc->pipes[i][0]);
		}
		i++;
	}
}
