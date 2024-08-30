/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:43:25 by yboumanz          #+#    #+#             */
/*   Updated: 2024/08/17 18:56:27 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (2147483648);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
		if ((res > INT_MAX && sign == 1) || (res > (2147483648) && sign == -1))
			return (2147483648);
	}
	if (str[i])
		return (2147483648);
	return (res * sign);
}
