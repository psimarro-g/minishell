/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 10:17:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 10:31:39 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_here_doc(t_parsemshell args, char *token, char *line, int *i)
{
	if (token != "<<")
		return (-1);
	//hacer el parseo
}
