/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:24:09 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 10:01:22 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ms_lst.h"

void	ms_lstdelone(t_cmdlist *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return ;
	if (lst->cmd)
		free(lst->cmd);
	if (lst->path)
		free(lst->path);
	while (lst->args && lst->args[i])
	{
		free(lst->args[i]);
		i++;
	}
	if (lst->args)
		free(lst->args);
	free(lst);
}
