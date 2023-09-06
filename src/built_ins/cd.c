/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:25:55 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 09:36:30 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//In bash if it doesnt find the var, it doesnt create it
int	cd(char *path, char **cwd, char ***envp)
{
	char	*tmp;

	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		free(tmp);
		return 1;
	}
	tmp = ft_getcwd();
	if (tmp)
	{
		set_env("OLDPWD", *cwd, envp);
		free(*cwd);
		*cwd = tmp;
	}
	printf("DEBUG: Function cd: PWD Despues del cambio: %s\n", *cwd);
	set_env("PWD", *cwd, envp);
	return (0);
}