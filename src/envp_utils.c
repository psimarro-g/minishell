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
	if ((*envp) == NULL)
	{
		new_env = ft_strjoin(var_equals, value);
		(*envp) = add_new_var(*envp, new_env);
		free(new_env); 
	}
	else
	{
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

char	**clone_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
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
