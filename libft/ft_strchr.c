/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:01:16 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/08 15:29:08 by yboumanz         ###   ########.fr       */
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
