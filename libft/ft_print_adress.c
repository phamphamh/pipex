/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:14:21 by yboumanz          #+#    #+#             */
/*   Updated: 2024/07/13 04:11:51 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		putnbr_ptr(nb / 16);
		putnbr_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_putchar_fd((nb + '0'), 1);
		else
			ft_putchar_fd((nb - 10 + 'a'), 1);
	}
}

int	ptr_len(uintptr_t nb)
{
	int	len;

	len = 0;
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}

int	ft_print_adress(void *ptr)
{
	int			print_len;
	uintptr_t	p;

	p = (uintptr_t)ptr;
	print_len = 0;
	if (ptr == 0)
		return (print_len += putstr_len("(nil)", 1));
	print_len += write(1, "0x", 2);
	if (p != 0)
	{
		putnbr_ptr(p);
		print_len += ptr_len(p);
	}
	return (print_len);
}
