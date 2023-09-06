/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:56:24 by dmontoro         ###   ########.fr       */
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

static void	pipe_heredoc(t_mshell *args, char *eof)
{
	pid_t	id;
	int		fd[2];
	char	*input;

	if (pipe(fd) == -1)
		ft_error(NULL, args, 1);
	id = fork();
	if (id == 0)
	{
		here_doc_signals();
		close(fd[0]);
		g_executing = 1;
		while (1)
		{
			input = readline("heredoc> ");
			if (input != NULL && ft_strlen(input) == 0)
			{
				free(input);
				continue ;
			}
			if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
			{
				free(eof);
				close(fd[1]);
				g_executing = 0;
				exit(EXIT_SUCCESS);
			}
			write(fd[1], input, ft_strlen(input));
			write(fd[1], "\n", 1);
			free(input);
		}
	}
	else
		parent_process_hd(fd, args, id);
	free(eof);
}

static void	hd_error(t_mshell *args, char *eof, char *line, int *i)
{
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

int	parse_here_doc(t_mshell *args, char *token, char *line, int *i)
{
	char	*eof;
	int		j;

	j = 0;
	if (ft_strncmp(token, "<<", 2))
		return (-1);
	*i -= (ft_strlen(token) - 2);
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	if (is_token(line, *i) || !line[*i])
	{
		hd_error(args, eof, line, i);
		return (0);
	}
	while (!ft_isspace(line[*i + j]) && !is_token(line, *i + j) && line[*i + j] != '\0')
		j++;
	eof = ft_substr(line, *i, j);
	//printf("DEBUG: Function parse_here_doc: eof: \'%s\'\n", eof);
	pipe_heredoc(args, eof);
	*i += j;
	return (0);
}
