/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:42:36 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/16 10:48:16 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

void	ms_lstadd_back(t_cmdlist **lst, t_cmdlist *new)
{
	t_cmdlist		*last;

	if (!lst || !new)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		last = ms_lstlast(*lst);
		last->next = new;
		new->pre = last;
	}
}
