/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:26:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/29 10:20:09 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//args is the array of arguments of the command (in case of normal execution)
//status is the status of the last command executed
int	ft_exit(char **args, int status)
{
	int	i;

	i = 1;
	while (args && args[i] != NULL)
		i++;
	printf("exit\n");
	printf("DEBUG: Function ft_exit: exiting\n");
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return 1;
	}
	if (i == 1)
		exit(0);
	if (ft_atoi(args[1]) == -1)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		return 1;
	}
	exit(ft_atoi(args[1]));
}
