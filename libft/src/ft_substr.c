/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:58:33 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:58:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*cpstr;

	if (!s)
		return (0);
	if (!len || start > ft_strlen(s))
		return (ft_calloc(sizeof(char), 1));
	cpstr = ft_calloc(sizeof(char), len + 1);
	if (!cpstr)
		return (0);
	i = 0;
	while ((char)s[start] && len--)
		cpstr[i++] = (char)s[start++];
	return (cpstr);
}
