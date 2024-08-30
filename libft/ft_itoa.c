/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:18:50 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/02 17:13:00 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_dig_sign(int num)
{
	int	dig;

	dig = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		dig++;
	while (num != 0)
	{
		num /= 10;
		dig++;
	}
	return (dig);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		dig;
	long	num;

	num = n;
	dig = count_dig_sign(n);
	str = (char *)malloc(dig + 1);
	if (!str)
		return (NULL);
	str[dig] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	while (num != 0)
	{
		str[--dig] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
