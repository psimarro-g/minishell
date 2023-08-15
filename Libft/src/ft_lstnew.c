/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:47:43 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:47:48 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*elmt;

	elmt = (t_list *)ft_calloc(sizeof(*elmt), 1);
	if (!elmt)
		return (0);
	elmt->content = content;
	return (elmt);
}
