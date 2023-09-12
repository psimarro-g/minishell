/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:38:17 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/12 20:39:04 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s1[i] && s2[i] && ret == 0)
	{
		ret = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (ret == 0)
		ret = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (ret);
}
