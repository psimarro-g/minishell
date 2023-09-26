/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/26 18:53:09 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	parent_process_hd(int fd[2], t_mshell *args, pid_t id)
{
	t_cmdlist	*last;

	last = ms_lstlast(args->cmds);
	close(fd[1]);
	last->input = fd[0];
	ignore_signals();
	waitpid(id, &args->exit_status, 0);
	change_signals();
}

static void	child_hd(t_mshell *args, int fd[2], char *eof, int expand)
{
	char	*input;

	g_executing = 1;
	while (1)
	{
		input = readline("heredoc> ");
		if (input != NULL && ft_strlen(input) == 0)
		{
			write(fd[1], "\n", 1);
			free(input);
			continue ;
		}
		if (input == NULL || (ft_strcmp(input, eof) == 0))
		{
			free(eof);
			close(fd[1]);
			g_executing = 0;
			exit(EXIT_SUCCESS);
		}
		expand_heredoc(args, fd, input, expand);
		free(input);
	}
}

static void	pipe_heredoc(t_mshell *args, char *eof, int expand)
{
	pid_t	id;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(NULL, args, 1);
	id = fork();
	if (id == 0)
	{
		here_doc_signals();
		close(fd[0]);
		child_hd(args, fd, eof, expand);
	}
	else
		parent_process_hd(fd, args, id);
	free(eof);
}

int	parse_here_doc(t_mshell *args, char *token, char *line, int *i)
{
	char	*eof;
	int		expand;

	if (ft_strncmp(token, "<<", 2))
		return (-1);
	*i -= (ft_strlen(token) - 2);
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	if (is_token(line, *i) || !line[*i])
	{
		syntax_error(args, eof, line, i);
		return (0);
	}
	expand = get_eof(&eof, line, i);
	// printf("DEBUG: Function parse_here_doc: eof: \'%s\'\n", eof);
	pipe_heredoc(args, eof, expand);
	return (0);
}
