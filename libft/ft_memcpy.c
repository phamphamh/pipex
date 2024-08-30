/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:47:41 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/08 15:20:01 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*nat;
	const char	*str;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	nat = dest;
	str = src;
	while (i < n)
	{
		nat[i] = str[i];
		i++;
	}
	return (dest);
}
