/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:47:57 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/28 20:45:05 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path(char **envp, char *command, char *cwd);

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
		act->path = find_path(mshell->envp, aux, mshell->cwd);
		check_path(&act, act->path);
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
//Comprueba si path es relativo y valido y lo concatena si lo es y lo devuelve check_relative(ret) -> int si es valido
//Comprueba si path es abssoluyto y lo devuelve
//Busca el comando en PATH= y lo devuelve si está

static char	*check_absolute_path(char *command, char ***envp, char *cwd)
{
	char	*tmp;
	char 	*ret;
	char	*path;
	
	ret = NULL;
	path = ft_strdup(&command[1]);
	if (ft_strncmp(path, "~/", 2) == 0)
	{
		tmp = expand_var("$HOME", *envp, 0);
		ret = ft_strjoin(tmp, command);
		free(tmp);
	}
	else if (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "../", 3) == 0)
		ret = ft_strjoin(cwd, command);
	else if (command[1] == '/')
		ret = ft_strdup(path);
	if (ret && access(ret, F_OK | X_OK))
	{
		free(ret);
		ret = NULL;
	}
	free(path);
	return (ret);
}

static char	*find_path(char **envp, char *command, char *cwd)
{
	int i;
	char **paths;
	char *path;
	char *ret;

	i = 0;
	ret = check_absolute_path(command, &envp, cwd);
	if (ret)
		return (ret);
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], command);
		if (check_access(path, &ret) == 0)
			break ;
		i++;
		free(path);
	}
	free_split(paths);
	return (ret);
}
