/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:58:31 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 12:21:06 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	parse_char(const char c, int fd, va_list list)
{
	char	arg;

	if (c != 'c')
		return (-1);
	arg = va_arg(list, int);
	ft_putchar_fd(arg, fd);
	return (1);
}

int	parse_string(const char c, int fd, va_list list)
{
	char	*arg;

	if (c != 's')
		return (-1);
	arg = va_arg(list, char *);
	if (!arg)
		arg = "(null)";
	ft_putstr_fd(arg, fd);
	return (ft_strlen(arg));
}

int	parse_per(const char c, int fd, va_list list)
{
	char	arg;

	(void) list;
	arg = '%';
	if (c != '%')
		return (-1);
	write(fd, &arg, sizeof(char));
	return (1);
}
