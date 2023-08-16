/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 17:06:50 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:13:17 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	manage_width(t_tprint *tab, int k)
{
	if (!tab->left && !k)
	{
		while (tab->width > tab->len && (tab->width > tab->prcn || tab->n_p))
		{
			draw_width(tab);
			tab->width--;
		}
	}
	if (tab->left && k)
	{
		while (tab->width > tab->len && (tab->width > tab->prcn || tab->n_p))
		{
			draw_width(tab);
			tab->width--;
		}
	}
}

static void	manage_precision(t_tprint *tab, char c)
{
	if (c == 'p')
		tab->tlen += write(1, "0x", 2);
	while (tab->prcn > tab->len && tab->prcn > 0 && !tab->n_p)
	{
		draw_precision(tab);
		tab->prcn--;
	}
}

static void	manage_chr(t_tprint *tab, char *nn)
{
	int			i;

	i = -1;
	if (tab->len == 1 && tab->h_p && tab->prcn == 0 && *nn == '0' && !tab->h_w)
		tab->len = 0;
	if (tab->len == 1 && tab->h_p && tab->prcn == 0 && *nn == '0'
		&& tab->h_w && !tab->width)
		tab->len = 0;
	if (tab->len == 1 && tab->h_p && tab->prcn == 0 && *nn == '0' && !tab->plus)
		tab->tlen += write(1, " ", 1);
	else if (tab->len == 1 && tab->h_p && tab->prcn == 0
		&& *nn == '0' && tab->plus)
		return ;
	else if (tab->len > 0)
		while (nn[++i])
			tab->tlen += write(1, &nn[i], 1);
}

static char	*get_number(char c, va_list *args, t_tprint *tab)
{
	char	*nn;

	if (c == 'i' || c == 'd')
		nn = ft_itoa(va_arg(*args, int));
	else if (c == 'u')
		nn = ft_itoa(va_arg(*args, unsigned int));
	else if (c == 'x' || c == 'X')
		nn = is_pnt_or_hex(tab, va_arg(*args, unsigned int), c);
	else if (c == 'p')
		nn = is_pnt_or_hex(tab, va_arg(*args, unsigned long int), c);
	else
		return (0);
	return (nn);
}

void	print_any_num(t_tprint *tab, va_list *args, char c)
{
	char		*nn;
	char		*fnn;

	nn = get_number(c, args, tab);
	fnn = nn;
	tab->len = ft_strlen(nn);
	sign(tab, &nn, c);
	manage_width(tab, 0);
	sign_draw(tab, 0, nn, c);
	manage_precision(tab, c);
	manage_chr(tab, nn);
	manage_width(tab, 1);
	free(fnn);
	empty(tab);
}
