/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:32:10 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 08:16:51 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	word_size(const char *s)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i] && !ft_isspace(s[i]))
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

static int	skip_char(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

int static	copy_word(char **ret, const char *s, int *indexes, char **envp)
{
	int		comillas;
	int		size;
	char	*translation;

	comillas = (check_comillas('\'', s, indexes[1]) || \
		check_comillas('\"', s, indexes[1]));
	ret[indexes[0]] = ft_substr(s, (indexes[1]) + comillas, \
		word_size(&s[indexes[1]]) - comillas);
	if (!ret[indexes[0]])
		return (0);
	size = ft_strlen(ret[indexes[0]]);
	if (ret[indexes[0]][0] == '$')
	{
		translation = expand_var(ret[indexes[0]], envp);
		free(ret[indexes[0]]);
		ret[indexes[0]] = translation;
	}
	indexes[1] += word_size(&s[indexes[1]]) + comillas;
	indexes[1] += skip_char(&s[indexes[1]]);
	if (ret[indexes[0]])
		indexes[0]++;
	return (size);
}

//Indexes 0 = index de la palabra a escribir en ret y 1 = index de la linea
char	**split_and_expand(char const *s, int *i, char **envp)
{
	int		num_words;
	char	**ret;
	int		indexes[2];

	if (!s)
		return (NULL);
	indexes[0] = 0;
	indexes[1] = skip_char(&s[0]);
	num_words = count_words(s) + 1;
	ret = malloc((num_words) * sizeof(char *));
	if (!ret)
		return (NULL);
	ret[num_words - 1] = 0;
	while (--num_words > 0)
	{
		(*i) += copy_word(ret, s, &indexes[0], envp);
		if (!ret[indexes[0] - 1])
			return (NULL);
	}
	return (ret);
}
