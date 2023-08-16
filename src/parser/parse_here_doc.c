/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 12:48:36 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_here_doc(t_parsemshell *args, char *token, char *line, int *i)
{
	if (ft_strncmp(token, "<<", 2))
		return (-1);
	//hacer el parseo
	printf("parse_here_doc\n");
	return (0);
}
