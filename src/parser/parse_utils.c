/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:32:10 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/07 18:40:13 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_error(char *s, t_mshell *mshell, int exit_code)
{
	if (mshell)
		mshell->exit_status = exit_code;
	if (s)
		ft_putstr_fd(s, 1);
}

static int	word_size(const char *s)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (s[i] && !ft_isspace(s[i]) && !is_token(s, i))
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

void static	copy_word(char **ret, const char *s, int *indexes, t_mshell *mshell)
{
	int		comillas;
	char	*translation;

	comillas = (check_comillas('\'', s, indexes[1]) || \
		check_comillas('\"', s, indexes[1]));
	ret[indexes[0]] = ft_substr(s, (indexes[1]) + comillas, \
		word_size(&s[indexes[1]]) - comillas);
	if (!ret[indexes[0]])
		return ;
	if (ret[indexes[0]][0] == '$')
	{
		translation = expand_var(ret[indexes[0]], mshell->envp, mshell->exit_status);
		free(ret[indexes[0]]);
		ret[indexes[0]] = translation;
	}
	indexes[1] += word_size(&s[indexes[1]]) + comillas;
	indexes[1] += skip_char(&s[indexes[1]]);
	if (ret[indexes[0]])
		indexes[0]++;
}

//Indexes 0 = index de la palabra a escribir en ret y 1 = index de la linea
char	**split_and_expand(char const *s, int *i, t_mshell mshell)
{
	int		num_words;
	char	**ret;
	int		indexes[2];

	if (!s)
		return (NULL);
	indexes[0] = 0;
	indexes[1] = skip_char(&s[0]);
	num_words = count_words(s) + 1;
	ret = ft_calloc((num_words), sizeof(char *));
	if (!ret)
		return (NULL);
	while (--num_words > 0)
	{
		copy_word(ret, s, &indexes[0], &mshell);
		if (!indexes[0] || !ret[indexes[0] - 1])
			return (NULL);
	}
	ret[indexes[0]] = 0;
	(*i) += indexes[1];
	return (ret);
}
