/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:07:25 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:12:28 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	flags(t_tprint *tab)
{
	while (*tab->fid == '0' || *tab->fid == '-' || *tab->fid == '+'
		|| *tab->fid == ' ' || *tab->fid == '#')
	{
		if (*tab->fid == '0')
			tab->zero = 1;
		else if (*tab->fid == '-')
			tab->left = 1;
		else if (*tab->fid == ' ')
			tab->space = 1;
		else if (*tab->fid == '+')
			tab->plus = 1;
		else if (*tab->fid == '#')
			tab->hash = 1;
		if (tab->zero == 1 && tab->left == 1)
			tab->zero = 0;
		if (tab->plus == 1)
			tab->space = 0;
		tab->fid++;
	}
}

void	width(t_tprint *tab, va_list *args)
{
	tab->width = star(tab, args);
	if (!tab->h_w && *tab->fid != '.')
	{
		tab->width = ft_atoi((const char *)tab->fid);
		if (tab->width)
			while (*tab->fid >= '0' && *tab->fid <= '9')
				tab->fid++;
		tab->h_w = 1;
	}
	if (tab->width < 0)
	{
		tab->left = 1;
		tab->width = -tab->width;
	}
}

void	precision(t_tprint *tab, va_list *args)
{
	if (*tab->fid == '.')
	{
		tab->h_p = 1;
		tab->fid++;
		tab->prcn = star(tab, args);
		if (!tab->prcn)
		{
			tab->prcn = ft_atoi((const char *)tab->fid);
			if (tab->prcn)
				while (*tab->fid >= '0' && *tab->fid <= '9')
					tab->fid++;
		}
		if (tab->prcn < 0)
		{
			tab->n_p = 1;
			tab->prcn = -tab->prcn;
		}
	}
	else
		tab->h_p = 0;
}

void	empty(t_tprint *tab)
{
	int		auxcount;

	auxcount = tab->tlen;
	ft_bzero(tab, sizeof(*tab));
	tab->tlen = auxcount;
}

int	star(t_tprint *tab, va_list *args)
{
	if (*tab->fid == '*')
	{
		tab->fid++;
		if (!tab->h_p && !(*tab->fid >= '0' && *tab->fid <= '9'))
			tab->h_w = 1;
		return (va_arg(*args, int));
	}
	return (0);
}
