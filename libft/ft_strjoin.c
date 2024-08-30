/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:58:55 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/02 18:12:59 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
