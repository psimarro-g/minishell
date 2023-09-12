/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:42:13 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/12 14:10:21 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
if no space found keep getting quotes and strjoin them
if regular text is found strdup line and strjoin with quotes until space is found
if quotes, check if there are end quotes, if there are get the index of the end quote and continue
if the quotes are not closed return 0, this includes double quotes where end quote is preceeded by backslash
if single quotes, parse quoted string as usual
if double quotes, parse quoted string as usual but expand variables and mind special chars such as backslash
update *i value
*/

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joinstr;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	joinstr = ft_calloc(sizeof(char), len + 1);
	if (!joinstr)
		return (0);
	ft_strlcpy(joinstr, s1, ft_strlen(s1) + 1);
	if (s2)
	{
		ft_strlcat(joinstr, s2, len + 1);
		free(s2);
	}
	if (s1)
		free(s1);
	return (joinstr);
}

char	*get_var(const char *line, int *i)
{
	int		j;
	char	*ret;

	j = *i;
	while (line[j] && !ft_isspace(line[j]))
		j++;
	ret = ft_substr(line, *i, j - *i);
	*i = j;
	return (ret);
}

int	check_dquotes(const char *line, int i)
{
	while (line[i] && line[i] != '\"')
		i++;
	if (line[i] == '\"' && line[i - 1] != '\\')
		return (1);
	else if (!line[i])
		return (0);
	return (check_dquotes(line, i + 1));
}

char	*get_single_quotes(const char *line, int *i)
{
	int		j;
	char	*ret;

	j = check_comillas('\'', line, *i);
	ret = ft_substr(line, *i, j);
	*i += j + 1;
	return (ret);
}

//terminar double quotes
char	*get_double_quotes(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;

	j = *i + 1;
	while (line[j] != '\"')
	{
		while (line[j] && line[j] != '\"' && line[j] != '\\' && line[j] != '$')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, j, *i - j));
		*i = j;
		if (line[*i] == '$')
			ret = ft_strjoin_free(ret, expand_var(get_var(line, i), mshell->envp, mshell->exit_status));
		else if (line[*i] == '\\')
		{
			*i += 1;
			ret = ft_strjoin_free(ret, line[*i]);
		}
		j = *i + 1;
	}
	return (ret);
}

char	*get_tranche(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;
	
	j = *i;
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j))
	{
		while (line[j] && !ft_isspace(line[j]) && !is_token(line, j) \
			&& line[j] != '\'' && line[j] != '\"' && line[j] != '$')
			j++;
		ret = ft_strjoin_free(ret, ft_substr(line, j, *i - j));
		*i = j;
		if (line[j] == '$')
			ret = ft_strjoin_free(ret, expand_var(get_var(line, i), mshell->envp, mshell->exit_status));
		else if (line[j] == '\'' && check_comillas('\'', line, j))
			ret = ft_strjoin_free(ret, get_single_quotes(line, i));
		else if (line[j] == '\"' && check_dquotes(line, j + 1))
			ret = ft_strjoin_free(ret, get_double_quotes(mshell, line, i));
		j = *i + 1;
	}
	printf("DEBUG: parse_quotes.c: get_tranche: ret: %s\n", ret);
	return (ret);
}
