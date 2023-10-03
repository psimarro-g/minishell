/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:16:22 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 08:46:03 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//Sets the variable env to value, if it doesnt exist it creates it at the end of envp
//env is the variable name, value is the value
void	set_env(char *env, char *value, char ***envp)
{
	int		i;
	char	*var_equals;
	char	*new_env;

	i = 0;
	var_equals = ft_strjoin(env, "=");
	while ((*envp)[i] != NULL && ft_strncmp((*envp)[i], var_equals, ft_strlen(var_equals)) != 0)
		i++;
	if ((*envp)[i] == NULL)
	{
		//printf("DEBUG: %s doesnt exist, creating it\n", env);
		new_env = ft_strjoin(var_equals, value);
		(*envp) = add_new_var(*envp, new_env);
		free(new_env); 
	}
	else
	{
		//printf("DEBUG: Function set_env: %s exists, changing it\n", env);
		free((*envp)[i]);
		(*envp)[i] = ft_strjoin(var_equals, value);
	}
	free(var_equals);
}

//This doesnt free envp because it puts the old envps in the new array
char	**add_new_var(char **envp, char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] =envp[i];
		i++;
	}
	new_envp[i] = ft_strdup(new_var);
	new_envp[i + 1] = NULL;
	free(envp);
	return (new_envp);
}

//We could re-create the list, but moving it is more efficient (on time)
//Obviously if we delete a lot of vars the usage of space is not optimal
//Since we have space alocated for the deleted vars
char	**delete_var(char **envp, char *key)
{
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], key, ft_strlen(key)) != 0)
		i++;

	if (envp[i] == NULL)
		return (envp);

	free(envp[i]);
	while (envp[i] != NULL)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[i- 1] = NULL;
	return (envp);
}

char	**clone_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
