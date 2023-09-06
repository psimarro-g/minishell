/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:20:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:01:30 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

t_cmdlist	*ms_lstlast(t_cmdlist *lst)
{
	if (!lst)
		return (0);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
