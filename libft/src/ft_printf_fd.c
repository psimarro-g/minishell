/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:58:20 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 12:26:48 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/libft.h"

int	ft_printf_fd(int fd, char const *s, ...)
{
	va_list	list;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start(list, s);
	while (s[i])
	{
		if (s[i] != '%')
		{
			write(fd, &s[i], sizeof(char));
			++ret;
		}
		else
			ret += parse_var(s[++i], fd, list);
		++i;
	}
	va_end(list);
	return (ret);
}
