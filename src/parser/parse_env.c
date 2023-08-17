/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:46:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 08:24:33 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	parse_env(t_parsemshell *args, char *token, char *line, int *i)
{
	if (token[0] != '$')
		return (-1);
	(void) args;
	(void) line;
	(void) i;
	return (0);
}

//Var has already the = at the end
char	*ft_getenv(char **envp, char* var)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], var, ft_strlen(var)) != 0)
		i++;
	if(envp[i] == NULL)
		return (NULL);

	j = ft_strlen(var);
	ret = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
	return (ret);
}

char	*expand_var(char *var, char **envp)
{
	char	*var_name;
	char	*var_equals;
	char	*translation;

	var_name = ft_substr(var, 1, ft_strlen(var));
	var_equals = ft_strjoin(var_name, "=");
	translation = ft_getenv(envp, var_equals);
	free(var_name);
	free(var_equals);
	return (translation);
}
