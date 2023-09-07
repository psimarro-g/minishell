/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:42:13 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/07 20:30:26 by psimarro         ###   ########.fr       */
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
	return (joinstr);
}

char	*get_single_quotes(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;

	j = check_comillas('\'', line, *i);
	ret = ft_substr(line, *i, j);
	*i = j + 1;
	return (ret);
}

//terminar double quotes
char	*get_double_quotes(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;

	j = *i;
	while (line[j] && line[j] != '\"')
		j++;
	if (line[j] == '\"')
	{
		ret = ft_substr(line, *i, j - *i);
		*i = j + 1;
		return (ret);
	}
	else
	{
		ft_error("Error: double quotes not closed\n", mshell, 1);
		return (NULL);
	}
}

char	*get_tranche(t_mshell *mshell, const char *line, int *i)
{
	int		j;
	char	*ret;
	char	*tmp;
	
	j = *i;
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j))
	{
		tmp = ret;
		while (line[j] && !ft_isspace(line[j]) && !is_token(line, j) \
			&& line[j] != '\'' && line[j] != '\"' && line[j] != '$')
			j++;
		ret = ft_strjoin_free(tmp, ft_substr(line, j, *i - j));
		if (line[j] == '$')
			ret = ft_strjoin_free(tmp, expand_var(ret, mshell->envp, mshell->exit_status));
		else if (line[j] == '\'' && check_comillas('\'', line, *i))
			ret = ft_strjoin_free(tmp, get_single_quotes(mshell, line, i));
		else if (line[j] == '\"' && check_dquotes(line, *i))
			ret = ft_strjoin_free(tmp, get_double_quotes(mshell, line, i));
		free(tmp);
		j = *i;
	}
	printf("DEBUG: parse_quotes.c: get_tranche: ret: %s\n", ret);
	return (ret);
}
