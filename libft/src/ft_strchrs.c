/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:54:16 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:54:21 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strchrs(const char *str, char *set)
{
	int	i;

	while (*str)
	{
		i = 0;
		while (set[i])
		{
			if (*str == set[i])
				return ((char *)str);
			i++;
		}
		str++;
	}
	return (0);
}
