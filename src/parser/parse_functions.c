/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 07:47:57 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 11:26:31 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*find_path(char **envp, char *command);

int	parse_command(t_parsemshell *args, char *token, char *line, int *i)
{
	t_cmdlist	*new;
	char		*aux;

	new = malloc(sizeof(t_cmdlist));
	new->cmd = token;
	aux = ft_strjoin("/", token);
	//Poner que si path es null, de error 
	new->path = find_path(args->envp, aux);
	//Cambiar split_args para que pare al encontrar un caracter especial
	new->args = split_args(line, ' ');
	//Cambiar expand_args para que expanda las variables de entorno y sobreescriba en caso de que una no exista
	new->args = expand_args(new->args, args->envp);
	
	printf("cmd: %s\n", new->cmd);
	printf("path: %s\n", new->path);
	printf("args: ");
	int j = 0;
	while (new->args[j] != NULL)
	{
		printf("%s ", new->args[j]);
		j++;
	}
	printf("\n");

	//Añadir a la lista de comandos
	(void) line;
	(void) i;
	//ft_lstadd_back(&args.cmds, ft_lstnew(new));
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