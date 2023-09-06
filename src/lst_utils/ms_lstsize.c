/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 06:55:58 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:01:36 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

int	ms_lstsize(t_cmdlist *lst)
{
	int			i;
	t_cmdlist	*act;

	i = 0;
	act = lst;
	while (act)
	{
		i++;
		act = act->next;
	}
	return (i);
}
