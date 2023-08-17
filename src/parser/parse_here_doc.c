/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 11:41:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	parent_process_hd(int fd[2], t_mshell *args)
{
	t_cmdlist	*last;

	last = ms_lstlast(args->cmds);
	close(fd[1]);
	dup2(fd[0], last->input);
	wait(NULL);
}


int	parse_here_doc(t_mshell *args, char *token, char *line, int *i)
{
	// pid_t	id;
	// int		fd[2];
	// char	*eof;
	// char	*input;

	if (ft_strncmp(token, "<<", 2))
		return (-1);
	// *i += 2;
	// while (ft_isspace(line[*i]))
	// 	(*i)++;
	// while (!ft_isspace(line[*i]) && !is_token(line, *i) && line[*i] == '\0')
	// 	(*i)++;
	// if (line[*i] == '\0')
	// 	return (-1);
	// if (pipe(fd) == -1)
	// 	error_pipe();
	// id = fork();
	// if (id == 0)
	// {
	// 	close(fd[0]);
	// 	while (1)
	// 	{
	// 		input = readline("heredoc> ");
	// 		if (ft_strncmp(input, eof, ft_strlen(line)) == 0)
	// 			exit(EXIT_SUCCESS);
	// 		write(fd[1], line, ft_strlen(line));
	// 	}
	// }
	// else
	// 	parent_process_hd(fd, args);
return (0);
}
