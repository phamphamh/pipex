/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:40:13 by yboumanz          #+#    #+#             */
/*   Updated: 2024/07/13 04:12:03 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_else_ifs(const char *str, int i, va_list list)
{
	int	print_lengths;

	print_lengths = 0;
	if (str[i + 1] == 'c')
		print_lengths += putchar_len(va_arg(list, int), 1);
	else if (str[i + 1] == 's')
		print_lengths += putstr_len(va_arg(list, char *), 1);
	else if ((str[i + 1] == 'd' || str[i + 1] == 'i'))
		print_lengths += ft_putnbr_len(va_arg(list, int), 1);
	else if (str[i + 1] == 'u')
		print_lengths += ft_put_uns_nbr(va_arg(list, unsigned int));
	else if (str[i + 1] == 'X')
		print_lengths += ft_putnbr_hex(va_arg(list, unsigned int), 'X');
	else if (str[i + 1] == 'x')
		print_lengths += ft_putnbr_hex(va_arg(list, unsigned int), 'x');
	else if (str[i + 1] == '%')
		print_lengths += putchar_len('%', 1);
	else if (str[i + 1] == 'p')
		print_lengths += ft_print_adress(va_arg(list, void *));
	return (print_lengths);
}

int	ft_printf(const char *str, ...)
{
	va_list		list;
	int			print_lengths;
	int			i;

	if (!str)
		return (-1);
	print_lengths = 0;
	va_start(list, str);
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
			print_lengths += putchar_len(str[i], 1);
		else if (ft_strchr("cspdiuxX%", str[i + 1]))
		{
			print_lengths += print_else_ifs(str, i, list);
			i++;
		}
		i++;
	}
	va_end(list);
	return (print_lengths);
}
