/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:54:31 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:54:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *s)
{
	char	*aux;
	int		i;

	i = -1;
	aux = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!aux)
		return (0);
	while (s[++i])
		aux[i] = s[i];
	return (aux);
}
