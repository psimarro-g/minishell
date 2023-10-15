/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:25:55 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 11:34:48 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*check_home(char **path, char **envp)
{
	char	*tmp;
	char	*aux;

	if (ft_strncmp(*path, "~/", 2) == 0)
	{
		aux = ft_strdup(*path + 1);
		free(*path);
		tmp = expand_var("$HOME", envp, 0);
		*path = ft_strjoin(tmp, aux);
		free(tmp);
		free(aux);
	}
	return (*path);
}

//In bash if it doesnt find the var, it doesnt create it
int	cd(char **path, char **cwd, char ***envp)
{
	char	*tmp;
	int		ret;

	if (!*path)
	{
		tmp = expand_var("$HOME", *envp, 0);
		ret = cd(&tmp, cwd, envp);
		free(tmp);
		return (ret);
	}
	*path = check_home(path, *envp);
	if (chdir(*path) == -1)
	{
		ft_printf_fd(2, "minishell: cd: %s: %s\n", *path, strerror(errno));
		return (1);
	}
	tmp = ft_getcwd();
	if (tmp)
	{
		set_env("OLDPWD", *cwd, envp);
		free(*cwd);
		*cwd = tmp;
	}
	set_env("PWD", *cwd, envp);
	return (0);
}
