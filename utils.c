/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:09:03 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/17 16:16:15 by yboumanz         ###   ########.fr       */
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

void	handle_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

bool	find_count_exe(char **argv, int argc, t_pip *struc)
{
	int 	i;
	int		res;

	i = 0;
	res = 0;
	struc->here_doc = -1;
	struc->exec_pos = 0;
	while (argv[i])
	{
		if (!ft_strcmp("here_doc", argv[i]))
		{
			res += 1;
			struc->here_doc = i;
		}
		if (!ft_strcmp("./pipex", argv[i]))
		{
			struc->exec_pos = i;
			res = i;
		}
		i++;
	}
	if ((argc - res) != 5)
		return (0);
	return (1);
}
