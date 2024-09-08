/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 03:18:52 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/08 03:20:07 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_split_vars(size_t *i, size_t *j, int *index)
{
	*i = 0;
	*j = 0;
	*index = -1;
}

void	init_quotes(int *in_single_quotes, int *in_double_quotes)
{
	*in_single_quotes = 0;
	*in_double_quotes = 0;
}
