/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:58:08 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/21 22:18:13 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <dirent.h>

int	minishell(t_mshell *mshell, char *path, char ***envp)
{
	char	*aux[2];
	char	*ms_path;

	ms_path = ft_strjoin(path, "/minishell");
	aux[0] = strdup("minishell");
	aux[1] = NULL;
	if (ft_strcmp(mshell->cmds->cmd, "./minishell") == 0)
	{
		if (ft_strnstr(mshell->cwd, "minishell", ft_strlen(mshell->cwd)))
			execve("./minishell", &aux[0], *envp);
	}
	else if (path)
		execve(ms_path, &aux[0], *envp);
	else
	{
		printf("minishell: %s: command not found\n", "minishell");
		mshell->exit_status = 127;
	}
	free(aux[0]);
	free(ms_path);
	return (0);
}
