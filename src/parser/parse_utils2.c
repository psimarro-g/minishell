/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:58:19 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 12:09:41 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (!path || stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	check_path(t_cmdlist **act, char *path)
{
	if (path == NULL)
		return ;
	else if (is_directory(path))
	{
		free((*act)->path);
		(*act)->path = NULL;
	}
}

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

int	is_token(const char *s, int i)
{
	if (ft_strncmp(&s[i], ">>", 2) == 0 || ft_strncmp(&s[i], "<<", 2) == 0)
		return (2);
	else if (s[i] == '<' || s[i] == '>' || s[i] == '|')
		return (1);
	return (0);
}

int	count_words(char const *s)
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
		while (s[i] && !ft_isspace(s[i]))
			i++;
		while (s[i] && ft_isspace(s[i]))
			i++;
	}
	return (count);
}
