/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboumanz <yboumanz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 03:17:35 by yboumanz          #+#    #+#             */
/*   Updated: 2024/09/08 03:19:59 by yboumanz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_quote(char c, int *in_single_quotes, int *in_double_quotes)
{
	int tmp_single;
	int tmp_double;

	tmp_single = *in_single_quotes;
	tmp_double = *in_double_quotes;
	if (c == '\'' && !tmp_double)
		*in_single_quotes = !tmp_single;
	else if (c == '\"' && !tmp_single)
		*in_double_quotes = !tmp_double;
	return (*in_single_quotes || *in_double_quotes);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;
	int	in_single_quotes;
	int	in_double_quotes;

	i = 0;
	trigger = 0;
	init_quotes(&in_single_quotes, &in_double_quotes);
	while (*str)
	{
		if (!is_quote(*str, &in_single_quotes, &in_double_quotes) && *str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c && !in_single_quotes && !in_double_quotes)
			trigger = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < finish)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

static char	**fill_split(const char *s, char c, char **split)
{
	size_t	i;
	size_t	j;
	int		index;
	int		in_single_quotes;
	int		in_double_quotes;

	init_split_vars(&i, &j, &index);
	init_quotes(&in_single_quotes, &in_double_quotes);
	while (i <= ft_strlen(s))
	{
		if (!is_quote(s[i], &in_single_quotes, &in_double_quotes) && s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0 && !in_single_quotes && !in_double_quotes)
		{
			split[j] = word_dup(s, index, i);
			if (!split[j])
				return (ft_free_all(split, j));
			j++;
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	split = malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (fill_split(s, c, split));
}
