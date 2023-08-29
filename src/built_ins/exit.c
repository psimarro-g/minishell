/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:26:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/29 08:23:32 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_exit(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
		i++;
	printf("Exit");
	printf("DEBUG: Function ft_exit: exiting\n");
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return 1;
	}
	if (ft_atoi(args[1]) == -1)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		return 1;
	}
	exit(ft_atoi(args[1]));
}
