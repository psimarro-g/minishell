/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:37 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 12:08:08 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void process_token(char *line, t_parsemshell *args, int *i);

t_parsemshell	parse_line(char *line, char **envp, int (*parse_list[FUN_SIZE])(t_parsemshell *, char *, char *, int *))
{
	int				i; //indice de donde estamos en line
	t_parsemshell	args;
	
	i = 0;
	ft_bzero(&args, sizeof(t_parsemshell));
	args.envp = envp;
	args.parse_list = parse_list;
	while(line[i])
	{
		while(ft_isspace(line[i]))
			i++;
		process_token(line, &args, &i);
	}
	return (args);
}

char	*get_token(const char *line, int *i)
{
	int	start;
	int	end;
	int	quote;

	start = *i;
	quote = line[start] == '\'';
	while(line[*i] && (!ft_isspace(line[*i]) || quote))
	{
		if (line[*i] == '\'' && *i != start)
			quote = 0;
		(*i)++;
	}
	end = *i;
	return (ft_substr(line, start, end - start));
}

void add_token(t_parsemshell *args, char *token, char *line, int *i)
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

void	process_token(char *line, t_parsemshell *args, int *i)
{
	char	*token;

	if (!line[*i])
		return ;
	token = get_token(line, i);
	printf("token: %s\n", token); //DEBUG
	add_token(args, token, line, i);
	free(token);
}
