/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:40:20 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/17 15:11:21 by yboumanz         ###   ########.fr       */
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


void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*mem;

	mem = (malloc(num_elements * element_size));
	if (!mem)
		return (NULL);
	ft_bzero(mem, num_elements * element_size);
	return (mem);
}

