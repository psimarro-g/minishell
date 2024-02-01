/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:25:49 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 11:41:43 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_export(char **envp);
static int	check_var(char *str);
static char	*get_key(char *str);
static char	*get_value(char *str);

//Takes a pointer to the addres of envp and 
//the string with all the args of the command
//If value not given, it assigns the null string to value
int	export(char **args, char ***envp)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	if (!args[i])
	{
		print_export(*envp);
		return (0);
	}
	while (args[i])
	{
		if (!check_var(args[i]))
		{
			ft_printf_fd(2, "export: '%s': not a valid identifier\n", args[i]);
			return (1);
		}
		key = get_key(args[i]);
		value = get_value(args[i]);
		set_env(key, value, envp);
		free(key);
		free(value);
		i++;
	}
	return (0);
}

static void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

//Returns 0 if its an invalid variable name, 1 if its valid
static int	check_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

static char	*get_value(char *str)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = ft_substr(str, i + 1, ft_strlen(str) - i);
	return (value);
}
