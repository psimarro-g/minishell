/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:51:38 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:51:44 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long long int	ft_power(long long int base, long long int power)
{
	long long int	n_aux;

	if (!base)
		return (1);
	if (power < 0)
		return (0);
	n_aux = base;
	while (power-- > 1)
		base *= n_aux;
	return (base);
}
