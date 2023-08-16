/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 20:40:11 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:12:31 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	draw_width(t_tprint *tab)
{
	if (tab->zero && !tab->prcn && tab->n_p && !tab->left)
		tab->tlen += write(1, "0", 1);
	else if (tab->zero && tab->n_p && !tab->left)
		tab->tlen += write(1, "0", 1);
	else if (tab->zero && !tab->h_p && !tab->left)
		tab->tlen += write(1, "0", 1);
	else
		tab->tlen += write(1, " ", 1);
}

void	draw_precision(t_tprint *tab)
{
	if ((tab->zero || (tab->width && tab->prcn) || tab->h_p) && !tab->n_p)
	{
		tab->tlen += write(1, "0", 1);
		tab->zero = 1;
	}
	else
		tab->tlen += write(1, " ", 1);
	if (tab->left && tab->width)
		tab->width--;
}

void	hash(t_tprint *tab, char c, char *nn)
{
	if (!(tab->len == 1 && *nn == '0') && tab->hash && (c == 'x' || c == 'X'))
	{
		if (c == 'x')
			tab->tlen += write(1, "0x", 2);
		else if (c == 'X')
			tab->tlen += write(1, "0X", 2);
	}
	return ;
}	
