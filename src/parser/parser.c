/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:37 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 12:10:26 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	process_token(char *line, t_mshell *args, int *i);
static void	check_last_cmd(t_mshell *mshell);

void	parse_line(char *line, t_mshell *mshell)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		process_token(line, mshell, &i);
	}
	check_last_cmd(mshell);
}

static void	check_last_cmd(t_mshell *mshell)
{
	t_cmdlist	*last_cmd;
	char		*line;

	last_cmd = ms_lstlast(mshell->cmds);
	if (!last_cmd->cmd && !last_cmd->args && last_cmd->input == -1
		&& last_cmd->output == -1 && last_cmd->error == 0 && last_cmd->pre)
	{
		line = readline("> ");
		if (line && line[0] != '\n')
		{
			add_history(line);
			parse_line(line, mshell);
			free(line);
		}
		else
		{
			free(line);
			ft_error("minishell: syntax error: unexpected end of file\n",
				mshell, 0);
		}
	}
}

static char	*get_token(t_mshell *mshell, const char *line, int *i)
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

static void	add_token(t_mshell *args, char *token, char *line, int *i)
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

static void	process_token(char *line, t_mshell *args, int *i)
{
	char	*token;

	if (!line[*i])
		return ;
	token = get_token(args, line, i);
	add_token(args, token, line, i);
	free(token);
}
