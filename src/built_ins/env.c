/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:26:02 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 11:36:09 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//si strchr no encontrase el caracter, esto petaria, 
//pero siempre lo va a encontrar porque es una variable de entorno
int	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=')[1] != '\0')
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}
