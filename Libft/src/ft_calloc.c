/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:39:57 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:40:05 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*aux;

	if (size > INT_MAX / count || !count || !size)
		return (0);
	aux = malloc(count * size);
	if (!aux)
		return (0);
	ft_bzero(aux, count * size);
	return (aux);
}
