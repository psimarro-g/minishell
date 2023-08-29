/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:28:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/29 10:28:27 by dmontoro         ###   ########.fr       */
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
	new->input = dup(STDIN_FILENO);
	new->output = dup(STDOUT_FILENO);
	new->next = NULL;
	new->pre = NULL;
	return (new);
}