/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:58:19 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 07:57:37 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_comillas(char c, const char *s, int i)
{
	int	j;

	if (s[i] != c)
		return (0);
	j = i + 1;
	while (s[j] && s[j] != c)
		j++;
	if (s[j] == c)
		return (j - i);
	return (0);
}

static void	jump_quotes(char const *s, int *i, int *count)
{
	if (s[*i] == '\'')
	{
		while (s[++(*i)] && s[*i] != '\'')
			;
		(*i)++;
		(*count)++;
	}
	if (s[*i] == '\"')
	{
		while (s[++(*i)] && s[*i] != '\"')
			;
		(*i)++;
		(*count)++;
	}
}

void	jump_spaces(char const *s, int *i, int *found)
{
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	*found = 0;
}

int	count_words(char const *s)
{
	int	count;
	int	found;
	int	i;

	i = 0;
	found = 0;
	count = 0;
	while (s[i])
	{
		jump_quotes(s, &i, &count);
		while (s[i] && !ft_isspace(s[i]))
		{
			count += !found;
			found = 1;
			++i;
		}
		jump_spaces(s, &i, &found);
		if (s[i] && (s[i] == '<' || s[i] == '>' || s[i] == '|' || \
			ft_strncmp(&s[i], ">>", 2) == 0 || ft_strncmp(&s[i], "<<", 2) == 0))
			return (count);
	}
	return (count);
}
