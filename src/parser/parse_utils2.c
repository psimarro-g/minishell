/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:58:19 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/12 20:41:33 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int is_token(const char *s, int i)
{ 
	if (ft_strncmp(&s[i], ">>", 2) == 0 || ft_strncmp(&s[i], "<<", 2) == 0)
		return (2);
	else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		return (1);
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
	int	res;

	if (s[*i] == '\'')
	{
		while (s[++(*i)] && s[*i] != '\'')
			;
		(*i)++;
		(*count)++;
	}
	res = check_dquotes(s, *i);
	if (s[*i] == '\"' && res)
	{
		(*i) = res + 1;
		(*count)++;
	}
}

void	jump_spaces(char const *s, int *i, int *found)
{
	while (s[*i] && ft_isspace(s[*i]))
		(*i)++;
	*found = 0;
}

int		count_words(char const *s)
{
	int	count;
	int	found;
	int	i;

	i = 0;
	found = 0;
	count = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		count++;
		while(s[i] && !ft_isspace(s[i]))
			i++;
		while (s[i] && ft_isspace(s[i]))
			i++;
	}
	return (count);
}
