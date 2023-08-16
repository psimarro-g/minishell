/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_pnt_or_hex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:22 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:13:48 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static long long int	ft_ndigit_p(long long unsigned int n, \
	long long unsigned int base)
{
	long long unsigned int		n_dgt;

	n_dgt = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n_dgt++;
		n = n / base;
	}
	return (n_dgt);
}

char	*ft_itoa_base_p(long long unsigned int n, int base, char *elm_base)
{
	long long int			nn;
	char					*ret;
	int						i;
	long long unsigned int	b;

	b = base;
	nn = 0;
	i = ft_ndigit_p(n, base);
	if (n == 0)
		nn = 1;
	ret = ft_calloc(sizeof(char), i + 1);
	*(ret + i) = '\0';
	while (n > 0)
	{
		ret[--i] = elm_base[n % base];
		n = n / base;
	}
	if (nn == 1)
		*ret = '0';
	return (ret);
}

char	*is_pnt_or_hex(t_tprint *tab, long long unsigned int n, char c)
{
	char	*aux_ret;

	if (c == 'p' || (n != 0 && tab->hash))
		tab->width -= 2;
	if (c == 'X')
		aux_ret = ft_itoa_base(n, 16, EX_BASE_UP);
	else
		aux_ret = ft_itoa_base_p(n, 16, EX_BASE);
	return (aux_ret);
}

int	is_negative(t_tprint *tab, char **nn)
{
	if (**nn == '-')
	{
		tab->negative = 1;
		(*nn)++;
		if (tab->width > tab->prcn && tab->h_p)
		{
			tab->len--;
			tab->width--;
		}
		else if (tab->width == tab->prcn && tab->h_p)
			tab->len--;
		if (tab->h_p && tab->prcn > tab->width)
			tab->prcn++;
		return (1);
	}
	else
		return (0);
}
