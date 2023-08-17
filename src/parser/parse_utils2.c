/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:58:19 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 13:42:03 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_token(const char *s, int i)
{
	if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		return (1);
	else if (ft_strncmp(&s[i], ">>", 2) == 0 || ft_strncmp(&s[i], "<<", 2) == 0)
		return (2);
	return (0);
}

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
		if (s[i] && is_token(s, i))
			return (count);
	}
	return (count);
}
