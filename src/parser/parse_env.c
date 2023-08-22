/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:46:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/22 11:44:12 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int	parse_env(t_mshell *args, char *token, char *line, int *i)
{
	if (token[0] != '$')
		return (-1);

	return (parse_command(args, token, line, i));
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

//returns null if var doesnt start with $
char	*expand_var(char *var, char **envp)
{
	char	*var_name;
	char	*var_equals;
	char	*translation;

	if (var[0] != '$')
		return (NULL);

	var_name = ft_substr(var, 1, ft_strlen(var));
	var_equals = ft_strjoin(var_name, "=");
	translation = ft_getenv(envp, var_equals);
	if (translation && translation[0] == '$')
		translation = expand_var(translation, envp);
	free(var_name);
	free(var_equals);
	return (translation);
}
