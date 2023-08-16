/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:47:27 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:47:33 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*pstn_new;
	t_list	*pstn_old;

	new_lst = ft_lstnew((*f)(lst->content));
	if (!lst || !new_lst)
		return (0);
	pstn_new = new_lst;
	pstn_old = lst->next;
	while (pstn_old)
	{
		pstn_new->next = ft_lstnew((*f)(pstn_old->content));
		if (!pstn_new->next)
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		pstn_new = pstn_new->next;
		pstn_old = pstn_old->next;
	}
	return (new_lst);
}
