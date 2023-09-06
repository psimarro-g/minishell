/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 08:13:39 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 09:59:17 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Echo -nnnnnnnn hola = hola$
//Echo -nnnnnnnnHola = -nnnnnnnnHola
int	echo(char **args)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		n = 2;
		while (args[i][n] == 'n')
			n++;
		if (args[i][n] != '\0')
			n = 0;
	}
	i += n > 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
