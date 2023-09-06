/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:27:08 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:01:09 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

void	ms_lstclear(t_cmdlist **lst)
{
	t_cmdlist	*last;

	if (!lst)
		return ;
	while (*lst)
	{
		last = (*lst)->next;
		ms_lstdelone(*lst);
		*lst = last;
	}
}
