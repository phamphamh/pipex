/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:22:27 by yboumanz          #+#    #+#             */
/*   Updated: 2024/06/08 22:13:01 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t element_size)
{
	void	*mem;

	mem = (malloc(num_elements * element_size));
	if (!mem)
		return (NULL);
	ft_bzero(mem, num_elements * element_size);
	return (mem);
}
