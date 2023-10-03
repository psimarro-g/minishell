/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:46:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 11:14:42 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_env(t_mshell *args, char *token, char *line, int *i)
{
	if (!token || token[0] != '$')
		return (-1);
	return (parse_command(args, token, line, i));
}

// Var has already the = at the end
static char	*ft_getenv(char **envp, char *var)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], var, ft_strlen(var)) != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	j = ft_strlen(var);
	ret = ft_substr(envp[i], j, ft_strlen(envp[i]) - j);
	return (ret);
}

// returns null if var doesnt start with $
char	*expand_var(char *var, char **envp, int ret_code)
{
	char	*var_name;
	char	*var_equals;
	char	*translation;

	if (var[0] != '$')
		return (NULL);
	if (!var[1])
		return (ft_strdup("$"));
	var_name = ft_substr(var, 1, ft_strlen(var));
	if (ft_strncmp(var_name, "?", 1) == 0)
	{
		free(var_name);
		return (ft_itoa(ret_code));
	}
	var_equals = ft_strjoin(var_name, "=");
	translation = ft_getenv(envp, var_equals);
	if (translation && translation[0] == '$')
		translation = expand_var(translation, envp, ret_code);
	free(var_name);
	free(var_equals);
	return (translation);
}
