/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:37 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/12 20:36:47 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void process_token(char *line, t_mshell *args, int *i);

void	parse_line(char *line, t_mshell *mshell)
{
	int	i; //indice de donde estamos en line
	
	i = 0;
	while(line[i])
	{
		while(ft_isspace(line[i]))
			i++;
		process_token(line, mshell, &i);
	}
}

static int	consume_token(const char *line, int *i)
{
	int	j;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (ft_strncmp(&line[*i], ">>", 2) == 0 || ft_strncmp(&line[*i], "<<", 2) == 0)
		return (2);
	else if (is_token(line, *i))
		return (1);
	return (0);
}

char	*get_token(t_mshell *mshell, const char *line, int *i)
{
	int		size;
	char	*ret;

	size = is_token(line, *i);
	if (size == 0)
		ret = get_tranche(mshell, line, i);
	else
	{
		ret = ft_substr(line, *i, size);
		(*i) += size;
	}
	return (ret);
}

void add_token(t_mshell *args, char *token, char *line, int *i)
{
	int	code;
	int	j;

	code = -1;
	j = 0;
	while (code == -1)
	{
		code = (*args->parse_list[j])(args, token, line, i);
		j++;
	}
}

void	process_token(char *line, t_mshell *args, int *i)
{
	char	*token;

	if (!line[*i])
		return ;
	token = get_token(args, line, i);
	//printf("DEBUG: Function process_token: token: %s\n", token); //DEBUG
	add_token(args, token, line, i);
	free(token);
}

