/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:32:10 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 10:31:39 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	word_size(const char *s, char c)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i] && s[i] != c)
	{
		if (check_comillas('\'', s, i))
		{
			if (i == 0)
				return (check_comillas('\'', s, i));
			return (ret);
		}
		if (check_comillas('\"', s, i))
		{
			if (i == 0)
				return (check_comillas('\"', s, i));
			return (ret);
		}
		ret++;
		i++;
	}
	return (ret);
}

static int	skip_char(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i])
		i++;
	return (i);
}

void static	copy_word(char **ret, const char *s, char c, int *indexes)
{
	int	comillas;

	comillas = (check_comillas('\'', s, indexes[1]) || \
		check_comillas('\"', s, indexes[1]));
	ret[indexes[0]] = ft_substr(s, (indexes[1]) + comillas, \
		word_size(&s[indexes[1]], c) - comillas);
	if (!ret[indexes[0]])
		return ;
	indexes[1] += word_size(&s[indexes[1]], c) + comillas;
	indexes[1] += skip_char(&s[indexes[1]], c);
	indexes[0]++;
}

char	**split_args(char const *s, char c)
{
	int		num_words;
	char	**ret;
	int		indexes[2];

	if (!s)
		return (NULL);
	indexes[0] = 0;
	indexes[1] = skip_char(&s[0], c);
	num_words = count_words(s, c) + 1;
	ret = malloc((num_words) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[num_words - 1] = 0;
	while (--num_words > 0)
	{
		copy_word(ret, s, c, &indexes[0]);
		if (!ret[indexes[0] - 1])
			return (NULL);
	}
	return (ret);
}
