/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:28:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/26 18:09:10 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

t_cmdlist	*ms_lstnew(char *cmd, char *path, char **args)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->path = path;
	new->args = args;
	new->input = -1;
	new->output = -1;
	new->next = NULL;
	new->pre = NULL;
	new->error = 0;
	return (new);
}
