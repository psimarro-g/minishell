/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:47:57 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 08:00:51 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path(char **envp, char *command);

//Coge el token, lo expande, clona el comando, busca el path y coge sus argumentos y los expande si es necesario
int	parse_command(t_mshell *mshell, char *token, char *line, int *i)
{
	t_cmdlist	*act;
	char		*aux;
	char		*translation;

	act = ms_lstlast(mshell->cmds);
	translation = expand_var(token, mshell->envp, mshell->exit_status);
	if (translation == NULL)
		translation = ft_strdup(token);
	act->cmd = ft_strdup(translation);
	aux = ft_strjoin("/", translation);
	act->path = find_path(mshell->envp, aux);
	act->args = split_and_expand(line + (*i) - ft_strlen(token), i, *mshell);
	(*i) -= ft_strlen(token);
	mshell->num_commands++;
	free(translation);
	free(aux);
	return (0);
}

static int	check_access(char *path, char **ret)
{
	if (access(path, F_OK | X_OK) == 0)
	{
		*ret = ft_strdup(path);
		free (path);
		return (0);
	}
	else
		return (1);
}

static void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static char	*find_path(char **envp, char *command)
{
	int		i;
	char	**paths;
	int		j;
	char	*path;
	char	*ret;

	i = 0;
	ret = NULL;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	j = -1;
	path = ft_substr(command, 1, ft_strlen(command));
	while (j == -1 || paths[j] != NULL)
	{
		if (j != -1)
			path = ft_strjoin(paths[j], command);
		if (check_access(path, &ret) == 0)
			break ;
		j++;
		free (path);
	}
	free_split(paths);
	return (ret);
}