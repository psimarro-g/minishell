/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:25:06 by psimarro          #+#    #+#             */
/*   Updated: 2022/09/30 18:13:04 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*get_spec(const char **format)
{
	char	*aux;

	if (!ft_strchrs(*format + 1, FSPECS))
		return (0);
	aux = ft_substr(*format, 1, ft_strlen(*format)
			- ft_strlen(ft_strchrs(*format + 1, FSPECS)));
	*format = *format + ft_strlen(aux);
	return (aux);
}

void	fill_tab(t_tprint *tab, va_list *args)
{
	flags(tab);
	width(tab, args);
	precision(tab, args);
}

void	find_format(const char **format, va_list *args, t_tprint *tab)
{
	char	*t_end;
	char	*aux;

	if (**format == '%' && *format + 1)
	{
		tab->fid = get_spec(format);
		aux = tab->fid;
		if (tab->fid)
			fill_tab(tab, args);
		if (!tab->fid)
			return ;
		t_end = ft_strchrs(tab->fid, FSPECS);
		if (*t_end == 'c' || *t_end == '%')
			print_prc_char(tab, args, *t_end);
		else if (*t_end == 's')
			print_string(tab, args);
		else if (*t_end == 'i' || *t_end == 'd' || *t_end == 'x'
			|| *t_end == 'X' || *t_end == 'u' || *t_end == 'p')
			print_any_num(tab, args, *t_end);
		free(aux);
	}
	else if (!(*format + 1))
		return ;
	else
		tab->tlen += write(1, *format, 1);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	t_tprint	*tab;
	int			ret;

	tab = (t_tprint *)ft_calloc(1, sizeof(t_tprint));
	va_start(args, format);
	while (*format)
	{
		find_format(&format, &args, tab);
		format++;
	}
	va_end(args);
	ret = tab->tlen;
	free(tab);
	return (ret);
}
