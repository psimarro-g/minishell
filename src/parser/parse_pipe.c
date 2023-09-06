/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:36:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 13:30:46 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	parse_pipe(t_mshell *args, char *token, char *line, int *i)
{
	(void)i;
	(void)line;
	if (ft_strncmp(token, "|", 1))
		return (-1);
	ms_lstadd_back(&args->cmds, ms_lstnew(NULL, NULL, NULL));
	return (0);
}