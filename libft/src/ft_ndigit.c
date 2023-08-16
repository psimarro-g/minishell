/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ndigit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:50:40 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:50:47 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long long int	ft_ndigit(long long int n, long long unsigned int base)
{
	long long unsigned int		n_dgt;

	n_dgt = 0;
	if (n < 0)
		n = -n;
	else if (n == 0)
		return (1);
	while (n)
	{
		n_dgt++;
		n = n / base;
	}
	return (n_dgt);
}
