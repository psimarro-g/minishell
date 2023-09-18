/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:58:19 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/18 11:35:05 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	cpy_lst(char **to, char **from, int start)
{
	int	i;

	i = 0;
	while (from[i])
	{
		to[start + i] = ft_strdup(from[i]);
		free(from[i]);
		i++;
	}
	
}

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
