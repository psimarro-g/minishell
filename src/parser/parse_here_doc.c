/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 13:44:33 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	parent_process_hd(int fd[2], t_mshell *args)
{
	t_cmdlist	*last;

	last = ms_lstlast(args->cmds);
	close(fd[1]);
	last->input = fd[0];
	wait(NULL);
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
		close(fd[0]);
		while (1)
		{
			input = readline("heredoc> ");
			if (ft_strncmp(input, eof, ft_strlen(input)) == 0)
			{
				free(eof);
				close(fd[1]);
				exit(EXIT_SUCCESS);
			}
			write(fd[1], input, ft_strlen(input));
		}
	}
	else
		parent_process_hd(fd, args);
}

int	parse_here_doc(t_mshell *args, char *token, char *line, int *i)
{
	char	*eof;
	int		j;

	j = 0;
	if (ft_strncmp(token, "<<", 2))
		return (-1);
	while (ft_isspace(line[*i]))
		(*i)++;
	while (!ft_isspace(line[*i + j]) && !is_token(line, *i + j) && line[*i + j] != '\0')
		j++;
	if (is_token(line, *i))
	{
		eof = ft_substr(line, *i, is_token(line, *i));
		printf("minishell: syntax error near unexpected token `%s'\n", eof);
		ft_error(NULL, args, 1);
		free(eof);
		return (0);
	}
	eof = ft_substr(line, *i, j);
	printf("eof: .%s.\n", eof);
	pipe_heredoc(args, eof);
	*i += j;
	return (0);
}
