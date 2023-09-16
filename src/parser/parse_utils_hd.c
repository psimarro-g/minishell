/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_hd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:35:02 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/16 12:17:38 by psimarro         ###   ########.fr       */
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

int	get_eof(char *eof, char *line, int *i)
{
	int	j;
	int	expand;

	j = *i;
	expand = 1;
	eof = NULL;
	while (line[j] && !ft_isspace(line[j]) && !is_token(line, j))
	{
		while (line[j] && !ft_isspace(line[j]) && !is_token(line, j) \
			&& line[j] != '\'' && line[j] != '\"')
			j++;
		eof = ft_strjoin_free(eof, ft_substr(line, *i, j - *i));
		*i = j;
		if (line[*i] == '\'' && check_comillas('\'', line, j))
		{
			eof = ft_strjoin_free(eof, get_single_quotes(line, i));
			expand = 0;
		}	
		else if (line[*i] == '\"' && check_dquotes(line, j + 1))
		{
			eof = ft_strjoin_free(eof, get_dquotes_hd(line, i));
			expand = 0;
		}	
		j = *i;
	}
}

void	expand_heredoc(t_mshell *mshell, int fd[2], const char *line, int expand)
{
    if (expand)
    {
        write(fd[1], line, ft_strlen(line));
	    write(fd[1], "\n", 1);
    }
    else
    {
        write(fd[1], line, ft_strlen(line));
	    write(fd[1], "\n", 1);
    }
}
