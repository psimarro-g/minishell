/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:32:10 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/12 19:25:56 by psimarro         ###   ########.fr       */
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

	ret[indexes[0]] = get_tranche(mshell, s, &indexes[1]);
	if (!ret[indexes[0]])
		return ;
	indexes[1] += skip_char(&s[indexes[1]]);
	if (ret[indexes[0]])
		indexes[0]++;
}

//Indexes 0 = index de la palabra a escribir en ret y 1 = index de la linea
char	**split_and_expand(char const *s, int *i, t_mshell mshell, char *token)
{
	int		num_words;
	char	**ret;
	int		indexes[2];

	if (!s)
		return (NULL);
	indexes[0] = 1;
	indexes[1] = skip_char(&s[0]);
	num_words = count_words(s) + 1;
	ret = ft_calloc((num_words + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(token);
	while (--num_words > 0)
	{
		copy_word(ret, s, indexes, &mshell);
		if (!ret[indexes[0] - 1])
			break;
	}
	ret[indexes[0]] = 0;
	(*i) += indexes[1];
	return (ret);
}
