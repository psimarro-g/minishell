/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:10:24 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/06 16:33:02 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_filename(char *line, int *i)
{
	char	*file_name;
	int		j;

	j = 0;
	while (!ft_isspace(line[*i + j]) && !is_token(line, *i + j) && line[*i + j])
		j++;
	file_name = ft_substr(line, *i, j);
	*i += j;
	return (file_name);
}

static void	ms_open_file(t_mshell *args, char *argv, int i)
{
	int			file;
	t_cmdlist	*last;

	file = 0;
	if (i == 1)
		file = open(argv, O_RDONLY, 0777);
	else if (i == 2)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (i == 2 )
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	last = ms_lstlast(args->cmds);
	if (i == 1)
		last->input = file;
	else
		last->output = file;
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
	else if (!ft_strncmp(token, ">>", 2))
		file_option = 3;
	else
		return (-1);
	*i -= (ft_strlen(token) - is_token(token, 0));
	while (ft_isspace(line[*i]) && line[*i])
		(*i)++;
	if (is_token(line, *i) || !line[*i])
	{
		syntax_error(args, file_name, line, i);
		return (0);
	}
	file_name = get_filename(line, i);
	printf("DEBUG: Function parse_files: file_name: \'%s\'\n", file_name);
	ms_open_file(args, file_name, file_option);
	free(file_name);
	return (0);
}