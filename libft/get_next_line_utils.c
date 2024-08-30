/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:40:20 by yboumanz          #+#    #+#             */
/*   Updated: 2024/07/13 04:06:02 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	d;

	i = 0;
	d = c;
	while (str[i] != '\0')
	{
		if (str[i] == d)
			return ((char *)&str[i]);
		i++;
	}
	if (d == '\0')
		return ((char *)&str[i]);
	return ((char *) NULL);
}

void	ft_bzero(void *s, size_t n)
{
	char	*tab;
	size_t	i;

	tab = s;
	i = 0;
	while (i < n)
	{
		tab[i] = 0;
		i++;
	}
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*mem;

	mem = (malloc(num_elements * element_size));
	if (!mem)
		return (NULL);
	ft_bzero(mem, num_elements * element_size);
	return (mem);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*con;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	con = (char *)malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (!con)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		con[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		con[i + j] = s2[j];
		j++;
	}
	con [i + j] = '\0';
	return (con);
}
