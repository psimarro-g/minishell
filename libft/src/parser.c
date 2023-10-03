/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 20:58:18 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 12:21:17 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ini_arr(int (*fun[FUN_NMB])(char, int, va_list))
{
	fun[0] = & parse_char;
	fun[1] = & parse_string;
	fun[2] = & parse_per;
	fun[3] = & parse_int;
	fun[4] = & parse_uint;
	fun[5] = & parse_hexa;
	fun[6] = & parse_pointer;
}

int	parse_var(const char c, int fd, va_list list)
{
	int	(*function_list[FUN_NMB])(char, int, va_list);
	int	i;
	int	res;

	ini_arr(function_list);
	res = -1;
	i = 0;
	while (i < FUN_NMB && res == -1)
	{
		res = (*function_list[i])(c, fd, list);
		i++;
	}
	return (res);
}
