/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:33:19 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/02 18:32:32 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	mem_copy(const unsigned char *str, unsigned char *nat, size_t n)
{
	size_t	i;

	i = n;
	while (i > 0)
	{
		nat[i - 1] = str[i - 1];
		i--;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*nat;
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)src;
	nat = (unsigned char *)dest;
	i = 0;
	if (nat == str)
		return (dest);
	if (nat < str)
	{
		while (i < n)
		{
			nat[i] = str[i];
			i++;
		}
	}
	else
		mem_copy(str, nat, n);
	return (dest);
}
