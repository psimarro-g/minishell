/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:36:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/30 09:27:47 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/minishell.h"

int	parse_pipe(t_mshell *args, char *token, char *line, int *i)
{
	if (ft_strncmp(token, "|", 1))
		return (-1);
	*line = *line;
	ms_lstadd_back(&args->cmds, ms_lstnew(NULL, NULL, NULL));
	(*i)++;
	return (0);
}