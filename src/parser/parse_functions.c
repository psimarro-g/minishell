/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:47:57 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 11:57:20 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path(t_mshell *mshell, char *command);

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
		act->path = find_path(mshell, aux);
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

//Comprueba si path es relativo y valido y lo concatena si lo es 
//y lo devuelve check_relative(ret) -> int si es valido
//Comprueba si path es abssoluyto y lo devuelve
//Busca el comando en PATH= y lo devuelve si está

static char	*check_absolute_path(char *command, t_mshell *mshell, int *i)
{
	char		*tmp;
	char		*ret;
	char		*path;
	t_cmdlist	*act;

	ret = NULL;
	path = ft_strdup(&command[1]);
	if (ft_strncmp(path, "~/", 2) == 0)
	{
		tmp = expand_var("$HOME", mshell->envp, 0);
		ret = ft_strjoin(tmp, command);
		free(tmp);
	}
	else if (ft_strncmp(path, "./", 2) == 0 || ft_strncmp(path, "../", 3) == 0)
		ret = ft_strjoin(mshell->cwd, command);
	else if (command[1] == '/')
		ret = ft_strdup(path);
	if (ret && access(ret, F_OK | X_OK))
	{
		free(ret);
		ret = NULL;
		act = ms_lstlast(mshell->cmds);
		act->error = 1;
		ft_printf_fd(2, "minishell: %s: %s\n", path, strerror(errno));
		if (errno == ENOENT)
			mshell->exit_status = 127;
		else
			mshell->exit_status = 126;
	}
	free(path);
	*i = (!ft_strncmp(path, "~/", 2) || !ft_strncmp(path, "./", 2) || \
		!ft_strncmp(path, "../", 3) || command[1] == '/');
	return (ret);
}

static char	*find_path(t_mshell *mshell, char *command)
{
	int		i;
	char	**paths;
	char	*path;
	char	*ret;

	i = 0;
	ret = check_absolute_path(command, mshell, &i);
	if (ret)
		return (ret);
	if (i)
		return (NULL);
	i = 0;
	while (mshell->envp[i] && ft_strncmp(mshell->envp[i], "PATH=", 5) != 0)
		i++;
	if (!mshell->envp[i])
		return (NULL);
	paths = ft_split(mshell->envp[i] + 5, ':');
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
