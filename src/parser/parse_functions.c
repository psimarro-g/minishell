/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:47:57 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/21 15:38:07 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path(char **envp, char *command);

static char	**add_args(t_mshell *mshell, char *token, char *line, int *i)
{
	char		**ret;
	char		**new;
	int			size;
	t_cmdlist	*aux;
	int			ind;

	aux = ms_lstlast(mshell->cmds);
	size = 0;
	while (aux->args[size])
		size++;
	new = split_and_expand(line + (*i), i, *mshell, token);
	ind = 0;
	while (new[ind])
		ind++;
	ret = malloc((size + ind + 1) * sizeof(char *));
	cpy_lst(ret, aux->args, 0);
	cpy_lst(ret, new, size);
	ret[size + ind] = NULL;
	free(new);
	free(aux->args);
	return (ret);
}

// Coge el token, lo expande, clona el comando,
//busca el path y coge sus argumentos y los expande si es necesario
int	parse_command(t_mshell *mshell, char *token, char *line, int *i)
{
	t_cmdlist	*act;
	char		*aux;

	act = ms_lstlast(mshell->cmds);
	if (act->cmd == NULL)
	{
		act->cmd = ft_strdup(token);
		if (!act->cmd)
			return (0);
		aux = ft_strjoin("/", token);
		act->path = find_path(mshell->envp, aux);
		act->args = split_and_expand(line + (*i), i, *mshell, token);
		mshell->num_commands++;
		free(aux);
	}
	else
		act->args = add_args(mshell, token, line, i);
	return (0);
}

static int	check_access(char *path, char **ret)
{
	if (access(path, F_OK | X_OK) == 0)
	{
		*ret = ft_strdup(path);
		free(path);
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
	int i;
	char **paths;
	int j;
	char *path;
	char *ret;

	i = 0;
	ret = NULL;
	path = ft_substr(command, 1, ft_strlen(command));
	if (check_access(path, &ret) == 0)
		return (ret);
	free(path);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	j = 0;
	while (paths[j] != NULL)
	{
		path = ft_strjoin(paths[j], command);
		if (check_access(path, &ret) == 0)
			break ;
		j++;
		free(path);
	}
	free_split(paths);
	return (ret);
}