/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:39:10 by psimarro          #+#    #+#             */
/*   Updated: 2023/06/03 20:44:08 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static unsigned long long int	ft_checknb(unsigned long long int nb, int neg)
{
	unsigned long long int	nl;

	nl = 9223372036854775807;
	if (nb > nl && neg > 0)
		return (-1);
	if (nb > nl + 1 && neg < 0)
		return (0);
	return (nb);
}

int	ft_atoi(const char *str)
{
	int						i;
	int						neg;
	unsigned long long int	val;

	i = 0;
	neg = 1;
	val = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || \
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		neg *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		val = (val * 10) + (str[i++] - '0');
	val = ft_checknb(val, neg);
	return (neg * val);
}
