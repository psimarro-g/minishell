/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:26:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 12:30:14 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_number(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//args is the array of arguments of the command (in case of normal execution)
//status is the status of the last command executed
int	ft_exit(char **args, int status)
{
	int	i;

	i = 1;
	while (args && args[i] != NULL)
		i++;
	//printf("minishell $> exit\n");
	//printf("DEBUG: Function ft_exit: exiting\n");
	if (i > 2)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	if (i == 1)
		exit(status);
	if (!is_number(args[1]))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	exit((uint8_t)ft_atoi(args[1]));
}
