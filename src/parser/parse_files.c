/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:50:27 by psimarro          #+#    #+#             */
/*   Updated: 2023/10/15 13:26:11 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	handle_file_err(t_mshell *args, int file, char *argv, int i)
{
	t_cmdlist	*last;

	last = ms_lstlast(args->cmds);
	if (file == -1)
	{
		ft_printf_fd(2, "minishell: %s: %s\n", argv, strerror(errno));
		last->error = 1;
		args->exit_status = 1;
	}
	if (i == 1)
	{
		if (last->input != -1)
			close(last->input);
		last->input = file;
	}
	else
	{
		if (last->output != -1)
			close(last->output);
		last->output = file;
	}
}

static void	ms_open_file(t_mshell *args, char *argv, int i)
{
	int			file;
	t_cmdlist	*last;

	last = ms_lstlast(args->cmds);
	if (last->error)
		return ;
	file = 0;
	if (i == 1)
		file = open(argv, O_RDONLY, 0777);
	else if (i == 3)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	handle_file_err(args, file, argv, i);
}

int	parse_files(t_mshell *args, char *token, char *line, int *i)
{
	char	*file_name;
	int		file_option;

	file_option = 0;
	if (!ft_strncmp(token, "<", 1))
		file_option = 1;
	else if (!ft_strncmp(token, ">", 1))
		file_option = 2;
	if (!ft_strncmp(token, ">>", 2))
		file_option = 3;
	else if (!file_option)
		return (-1);
	*i -= (ft_strlen(token) - is_token(token, 0));
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	if (is_token(line, *i) || !line[*i])
	{
		syntax_error(args, line, i);
		return (0);
	}
	file_name = get_tranche(args, line, i);
	ms_open_file(args, file_name, file_option);
	free(file_name);
	return (0);
}
