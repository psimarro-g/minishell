/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:55:06 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/07 19:33:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joinstr;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	joinstr = ft_calloc(sizeof(char), len + 1);
	if (!joinstr)
		return (0);
	ft_strlcpy(joinstr, s1, ft_strlen(s1) + 1);
	if (s2)
		ft_strlcat(joinstr, s2, len + 1);
	return (joinstr);
}
