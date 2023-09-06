/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:36:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:00:31 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Erases the variable from the environment
int	unset(char **args, char ***envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		delete_var(*envp, args[i]);
		i++;
	}
	return (0);
}
