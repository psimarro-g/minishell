/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 18:58:08 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/23 16:51:41 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char *trim_puntos(char *line)
{
	int		i;
	char	*aux;

	i = ft_strlen(line) - 3;
	aux = NULL;
	while (line[i] != '/')
		i--;
	aux = ft_substr(line, 0, i + 1);
	free(line);
	printf ("debug: trimmed puntos '%s'\n", aux);
	return (aux);
}

char	*ft_trim_dir(char *mshell_dir)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	aux = NULL;
	while (mshell_dir[i])
	{
		while (mshell_dir[i] && mshell_dir[i] != '.')
			i++;
		aux = ft_strjoin_free(aux, ft_substr(mshell_dir, j, i - j));
		if (strncmp(&mshell_dir[i], "..", 2) == 0)
		{
			aux = trim_puntos(aux);
			i += 3;
		}
		else if (mshell_dir[i] == '.')
			i += 2;
		j = i;
		printf ("debug: trimmed path '%s'\n", aux);
	}
	printf ("debug: untrimmed path '%s'\n", mshell_dir);
	free(mshell_dir);
	return (aux);
}

int	minishell(t_mshell *mshell, char *path, char ***envp)
{
	char	*aux[2];
	char	*tmp;

	aux[0] = strdup("minishell");
	aux[1] = NULL;
	tmp = ft_strjoin(mshell->cwd, "/minishell");
	if (ft_strcmp(mshell->cmds->cmd, "./minishell") == 0)
	{
		if (ft_strcmp(path, tmp) == 0)
			execve("./minishell", &aux[0], *envp);
		else
			printf("minishell: %s: command not found\n", "./minishell");
	}
	else if (path)
		execve(path, &aux[0], *envp);
	else
	{
		printf("minishell: %s: command not found\n", "minishell");
		mshell->exit_status = 127;
	}
	free(tmp);
	free(aux[0]);
	return (0);
}
