/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:35:01 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 09:28:35 by psimarro         ###   ########.fr       */
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
	}
}
