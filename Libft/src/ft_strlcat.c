/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:55:50 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:55:56 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lens;
	size_t	leni;
	size_t	i;

	i = 0;
	lens = ft_strlen(src);
	leni = ft_strlen(dst);
	if (dstsize == 0)
		return (lens);
	else if (dstsize < leni)
		return (lens + dstsize);
	else
		lens = lens + leni;
	while (src[i] && leni + 1 < dstsize)
		dst[leni++] = src[i++];
	dst[leni] = 0;
	return (lens);
}
