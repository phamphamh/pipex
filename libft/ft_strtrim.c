/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:17:00 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/09 14:26:10 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	length;
	size_t	start;
	size_t	end;
	size_t	trimmed_length;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	length = ft_strlen(s1);
	start = 0;
	end = length - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end]))
		end--;
	trimmed_length = end - start + 1;
	trimmed_str = (char *)malloc(trimmed_length + 1);
	if (!trimmed_str)
		return (NULL);
	ft_memmove(trimmed_str, s1 + start, trimmed_length);
	trimmed_str[trimmed_length] = '\0';
	return (trimmed_str);
}
