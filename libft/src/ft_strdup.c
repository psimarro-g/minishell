/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:54:31 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/18 12:01:34 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	char	*aux;
	int		i;

	i = -1;
	if (!s)
		return (0);
	aux = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!aux)
		return (0);
	while (s[++i])
		aux[i] = s[i];
	return (aux);
}
