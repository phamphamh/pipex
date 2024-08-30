/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:24:20 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/05 14:20:10 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;
	char	*str;

	i = 0;
	str = ptr;
	while (i < num)
	{
		str[i] = value;
		i++;
	}
	return (ptr);
}
