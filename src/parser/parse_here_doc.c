/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 09:52:55 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	parent_process_hd(int fd[2])
{
	close(fd[1]);
	dup2(fd[0], 0);
	wait(NULL);
}


int	parse_here_doc(t_mshell *args, char *token, char *line, int *i)
{
	pid_t	id;
	int		fd[2];
	char	*line;
	char	*limiter;

	if (ft_strncmp(token, "<<", 2))
		return (-1);
	*i += 2;
	if (pipe(fd) == -1)
		error_pipe();
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				ft_perror("Error: get next line failed\n", 0);
			if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
		parent_process_hd(fd);
	return (0);
}
