/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:42:07 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:42:12 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_itoa(long long int n)
{
	unsigned long long	nn;
	char				*ret;
	int					i;
	int					s;

	i = ft_ndigit(n, 10);
	s = 0;
	if (n < 0 && ++i && ++s)
		nn = -n;
	else
		nn = n;
	ret = ft_calloc(sizeof(char), i + 1);
	if (nn == 0)
		ret[0] = '0';
	while (nn != 0)
	{
		ret[--i] = 48 + nn % 10;
		nn = nn / 10;
	}
	if (s == 1)
		ret[0] = '-';
	return (ret);
}
