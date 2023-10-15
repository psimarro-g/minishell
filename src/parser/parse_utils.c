/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:32:10 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 12:08:00 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	syntax_error(t_mshell *args, char *line, int *i)
{
	char	*eof;

	if (!line[*i])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		ft_error(NULL, args, 1);
		return ;
	}
	eof = ft_substr(line, *i, is_token(line, *i));
	printf("minishell: syntax error near unexpected token `%s'\n", eof);
	ft_error(NULL, args, 1);
	free(eof);
}

static int	skip_char(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	return (i);
}

static void	check_home_path(char **command, char ***envp)
{
	char	*tmp;
	char	*ret;

	tmp = expand_var("$HOME", *envp, 0);
	ret = ft_strjoin(tmp, &command[0][1]);
	free(*command);
	*command = ret;
}

static int	copy_word(char **ret, const char *s, int *indexes, t_mshell *mshell)
{
	ret[indexes[0]] = get_tranche(mshell, s, &indexes[1]);
	if (ft_strncmp(ret[indexes[0]], "~/", 2) == 0)
		check_home_path(&ret[indexes[0]], &mshell->envp);
	if (!ret[indexes[0]])
		return (0);
	indexes[1] += skip_char(&s[indexes[1]]);
	if (ret[indexes[0]])
		indexes[0]++;
	return (1);
}

// Indexes 0 = index de la palabra a escribir en ret y 1 = index de la linea
char	**split_and_expand(char const *s, int *i, t_mshell mshell, char *token)
{
	int		num_words;
	char	**ret;
	int		indexes[2];

	if (!s)
		return (NULL);
	indexes[0] = 1;
	indexes[1] = skip_char(&s[0]);
	num_words = count_words(s) + 1;
	ret = ft_calloc((num_words + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	ret[0] = ft_strdup(token);
	while (--num_words > 0)
	{
		if (!copy_word(ret, s, indexes, &mshell))
			break ;
	}
	ret[indexes[0]] = 0;
	(*i) += indexes[1];
	return (ret);
}
