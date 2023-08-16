/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:56:25 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:56:29 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				i;
	unsigned int	sz;
	char			*ret;

	i = 0;
	if (!s || !f)
		return (0);
	sz = ft_strlen(s) + 1;
	ret = ft_calloc(sizeof(char), sz);
	if (!ret)
		return (0);
	ft_strlcpy(ret, s, sz);
	while (ret[i])
	{
		ret[i] = (*f)(i, ret[i]);
		i++;
	}
	return (ret);
}
