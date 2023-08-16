/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:57:58 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:58:02 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*lst_match;
	int		i;

	i = 0;
	while (*s)
	{
		if (*s++ == c)
		{
			lst_match = (char *)s;
			i++;
		}
		else if (c == 0 && *s == 0)
			return ((char *)s);
	}
	if (i == 0 && c == 0)
		return ((char *)s);
	else if (i == 0)
		return (0);
	return (--lst_match);
}
