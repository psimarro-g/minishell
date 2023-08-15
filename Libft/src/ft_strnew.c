/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 19:33:57 by psimarro          #+#    #+#             */
/*   Updated: 2023/03/23 19:36:49 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnew(size_t size)
{
	char	*rtn;

	rtn = (char *)malloc(size + 1);
	if (rtn != (char *) NULL)
		ft_bzero((void *)rtn, size + 1);
	return (rtn);
}
