/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:35:02 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/16 13:31:16 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_dquotes_hd(const char *line, int *i)
{
	int		j;
	char	*ret;
	char	*env_var;

	(*i)++;
	j = *i;
	ret = NULL;
	while (line[j] != '\"')
	{
		while (line[j] && line[j] != '\"' && line[j] != '\\')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, *i, j - *i));
		*i = j;
		if (line[*i] == '\\')
		{
			*i += 1;
			ret = ft_strjoin_free(ret, ft_substr(line, *i, 1));
		}
		j = *i;
	}
	(*i)++;
	return (ret);
}

int	get_eof(char **eof, char *line, int *i)
{
	int	j;
	int	expand;

	j = *i;
	expand = 1;
	*eof = NULL;
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j))
	{
		while (line[j] && !ft_isspace(line[j]) && !is_token(line, j) \
			&& line[j] != '\'' && line[j] != '\"')
			j++;
		*eof = ft_strjoin_free(*eof, ft_substr(line, *i, j - *i));
		*i = j;
		if (line[*i] == '\'' || line[*i] == '\"')
			expand = 0;
		if (line[*i] == '\'' && check_comillas('\'', line, j))
			*eof = ft_strjoin_free(*eof, get_single_quotes(line, i));
		else if (line[*i] == '\"' && check_dquotes(line, j + 1))
			*eof = ft_strjoin_free(*eof, get_dquotes_hd(line, i));
		j = *i;
	}
	return (expand);
}

static char	*parse_expand_hd(t_mshell *mshell, char *line)
{
	int		i;
	int		j;
	char	*ret;
	char	*env_var;

	i = 0;
	j = i;
	while (line[j])
	{
		while (line[j] && line[j] != '$')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, i, j - i));
		i = j;
		if (line[i] == '$')
		{
			env_var = get_var(line, &i);
			ret = ft_strjoin_free(ret, expand_var(env_var, mshell->envp, mshell->exit_status));
			free(env_var);
		}
		j = i;
	}
	return (ret);
}

void	expand_heredoc(t_mshell *mshell, int fd[2], char *line, int expand)
{
	char	*ret;

	ret = line;
    if (expand)
		ret = parse_expand_hd(mshell, line);
	write(fd[1], ret, ft_strlen(ret));
	write(fd[1], "\n", 1);
	if (expand && ret)
		free (ret);
}
