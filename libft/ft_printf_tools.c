/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:34:49 by yboumanz          #+#    #+#             */
/*   Updated: 2024/07/13 04:11:58 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putchar_len(char c, int fd)
{
	write (fd, &c, 1);
	return (1);
}

int	putstr_len(char *str, int fd)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	if (str)
	{
		while (str[i])
		{
			ft_putchar_fd(str[i], fd);
			i++;
		}
	}
	return (i);
}

int	ft_putnbr_len(int n, int fd)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		len += putstr_len("-2147483648", fd);
	else if (n >= 0 && n <= 9)
		len += putchar_len((n + '0'), fd);
	else if (n < 0)
	{
		len += putchar_len('-', fd);
		len += ft_putnbr_len((n * -1), fd);
	}
	else if (n >= 0 && n > 9)
	{
		len += ft_putnbr_len((n / 10), fd);
		len += ft_putnbr_len((n % 10), fd);
	}
	return (len);
}

int	ft_put_uns_nbr(unsigned int n)
{
	int	len;

	len = 0;
	if (n <= 9)
		len += putchar_len((n + '0'), 1);
	else
	{
		len += ft_putnbr_len((n / 10), 1);
		len += ft_putnbr_len((n % 10), 1);
	}
	return (len);
}

int	ft_putnbr_hex(unsigned int nbr, char c)
{
	int		len;
	long	nb;
	char	*base;

	nb = nbr;
	len = 0;
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb >= 16)
		len += ft_putnbr_hex(nb / 16, c);
	len += putchar_len(base[nb % 16], 1);
	return (len);
}
