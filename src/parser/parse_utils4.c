/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:37:00 by psimarro          #+#    #+#             */
/*   Updated: 2023/10/15 13:40:36 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_dquotes(const char *line, int i)
{
	while (line[i] && line[i] != '\"')
		i++;
	if (line[i] == '\"' && line[i - 1] != '\\')
		return (i);
	else if (!line[i])
		return (0);
	return (check_dquotes(line, i + 1));
}

void	handle_path_err(t_mshell *mshell, char **ret, char *path)
{
	t_cmdlist	*act;

	free(*ret);
	*ret = NULL;
	act = ms_lstlast(mshell->cmds);
	act->error = 1;
	ft_printf_fd(2, "minishell: %s: %s\n", path, strerror(errno));
	if (errno == ENOENT)
		mshell->exit_status = 127;
	else
		mshell->exit_status = 126;
}

char	*loop_paths(char **paths, char **path, char *command)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (paths[i] != NULL)
	{
		*path = ft_strjoin(paths[i], command);
		if (check_access(*path, &ret) == 0)
			break ;
		i++;
		free(*path);
	}
	return (ret);
}
