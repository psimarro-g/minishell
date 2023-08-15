/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:59:19 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:59:25 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_trimf(const char *str, char *set)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (!ft_strchr(set, str[i]) || (!ft_strchr(set, str[i + 1]) && *aux))
			aux[j++] = str[i++];
		else
			i++;
	}
	return (aux);
}
