/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:31 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:13:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	draw_before(t_tprint *tab)
{
	if (tab->width < tab->len && tab->zero && tab->plus && !tab->negative)
	{
		tab->tlen += write(1, "+", 1);
		tab->plus--;
	}
	if (tab->width > tab->len && !tab->h_p && tab->zero && tab->plus
		&& !tab->negative)
	{
		tab->tlen += write(1, "+", 1);
		tab->plus--;
	}
	if (tab->width < tab->len && tab->zero && tab->space && !tab->negative
		&& !tab->plus)
	{
		tab->tlen += write(1, " ", 1);
		tab->space--;
	}
	if (tab->width > tab->len && !tab->h_p && tab->zero && tab->space
		&& !tab->negative && !tab->plus)
	{
		tab->tlen += write(1, " ", 1);
		tab->space--;
	}
}

static void	draw_after(t_tprint *tab, char *nn, char c)
{
	if (tab->negative)
		tab->tlen += write(1, "-", 1);
	if (tab->plus && !tab->negative)
		tab->tlen += write(1, "+", 1);
	if (tab->space && !tab->negative && !tab->plus)
		tab->tlen += write(1, " ", 1);
	if (!(tab->h_w && tab->zero && !tab->h_p))
		hash(tab, c, nn);
}

void	sign_draw(t_tprint *tab, int k, char *nn, char c)
{
	if (k)
		draw_before(tab);
	else if (!k)
		draw_after(tab, nn, c);
}

static void	sign_negative(t_tprint *tab, char **nn)
{
	if (is_negative(tab, nn) && (!tab->h_p || tab->n_p) && tab->zero
		&& tab->negative--)
	{
		tab->space = 0;
		tab->tlen += write(1, "-", 1);
	}
	if (tab->negative)
		tab->space = 0;
}

void	sign(t_tprint *tab, char **nn, char c)
{
	sign_negative(tab, nn);
	if (tab->h_w && tab->zero && !tab->h_p)
		hash(tab, c, *nn);
	if (tab->plus && tab->width > tab->len && !tab->negative && tab->h_p
		&& tab->prcn == 0 && **nn != '0')
		tab->width--;
	else if (tab->plus && tab->width > tab->len && !tab->negative && !tab->h_p)
		tab->width--;
	else if (tab->plus && tab->width > tab->len && !tab->negative
		&& tab->h_p && tab->prcn > 0)
		tab->width--;
	if (tab->space && tab->width > tab->len && !tab->plus && !tab->negative
		&& tab->h_p && tab->prcn == 0 && **nn != '0')
		tab->width--;
	else if (tab->space && tab->width > tab->len && !tab->plus
		&& !tab->negative && !tab->h_p)
		tab->width--;
	else if (tab->space && tab->width > tab->len && !tab->plus
		&& !tab->negative && tab->h_p && tab->prcn > 0)
		tab->width--;
	sign_draw(tab, 1, *nn, c);
}
