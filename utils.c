/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 21:09:03 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/16 17:40:01 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

bool	find_count_exe(char **argv, int argc)
{
	int i;
	int	res;

	i = 0;
	res = 0;
	printf("%s", argv[0]);
	while (argv[i])
	{
		if (!ft_strcmp("./pipex", argv[i]))
			res = i;
		i++;
	}
	printf("%d", i);
	if ((argc - i) != 5)
		return (0);
	return (1);
}
