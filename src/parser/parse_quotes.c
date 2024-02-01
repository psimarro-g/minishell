/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:42:13 by psimarro          #+#    #+#             */
/*   Updated: 2023/10/15 13:44:01 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
if no space found keep getting quotes and strjoin them
if regular text is found strdup line and strjoin with quotes until space is found
if quotes, check if there are end quotes,
if there are get the index of the end quote and continue
if the quotes are not closed return 0,
this includes double quotes where end quote is preceeded by backslash
if single quotes, parse quoted string as usual
if double quotes, parse quoted string as usual but 
expand variables and mind special chars such as backslash
update *i value
*/

char	*get_var(const char *line, int *i)
{
	int		j;
	char	*ret;

	j = *i + 1;
	if (line[j] == '?')
	{
		ret = ft_strdup("$?");
		*i += 2;
		return (ret);
	}
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j) \
			&& line[j] != '$' && line[j] != '\'' && \
			(line[j] != '\"' || !(line[j] == '\"' && line[j - 1] != '\\')))
		j++;
	ret = ft_substr(line, *i, j - *i);
	*i = j;
	return (ret);
}

char	*get_single_quotes(const char *line, int *i)
{
	int		j;
	char	*ret;

	j = check_comillas('\'', line, *i);
	(*i)++;
	ret = ft_substr(line, *i, j - 1);
	*i += j;
	return (ret);
}

static void	handle_env(t_mshell *mshell, char **ret, const char *line, int *i)
{
	char	*env_var;

	env_var = get_var(line, i);
	*ret = ft_strjoin_free(*ret, expand_var(env_var, mshell->envp, \
			mshell->exit_status));
	free(env_var);
}

// terminar double quotes
static char	*get_double_quotes(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;

	(*i)++;
	j = *i;
	ret = NULL;
	while (line[j] != '\"')
	{
		while (line[j] && line[j] != '\"' && line[j] != '\\' && line[j] != '$')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, *i, j - *i));
		*i = j;
		if (line[*i] == '$')
			handle_env(mshell, &ret, line, i);
		else if (line[*i] == '\\')
		{
			*i += 1;
			ret = ft_strjoin_free(ret, ft_substr(line, *i, 1));
		}
		j = *i;
	}
	(*i)++;
	return (ret);
}

char	*get_tranche(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;

	j = *i;
	ret = NULL;
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j))
	{
		while (line[j] && !ft_isspace(line[j]) && !is_token(line, j)
			&& line[j] != '\'' && line[j] != '\"' && line[j] != '$')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, *i, j - *i));
		*i = j;
		if (line[*i] == '$')
			handle_env(mshell, &ret, line, i);
		else if (line[*i] == '\'' && check_comillas('\'', line, j))
			ret = ft_strjoin_free(ret, get_single_quotes(line, i));
		else if (line[*i] == '\"' && check_dquotes(line, j + 1))
			ret = ft_strjoin_free(ret, get_double_quotes(mshell, line, i));
		j = *i;
	}
	return (ret);
}
