/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:23:39 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/03 13:39:05 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	int		i;

	if (!f || !s)
		return (NULL);
	dest = ft_strdup((char *)s);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (dest[i] != '\0')
	{
		dest[i] = (*f)(i, dest[i]);
		i++;
	}
	return (dest);
}
