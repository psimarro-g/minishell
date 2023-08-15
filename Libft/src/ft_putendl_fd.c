/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:52:17 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:52:21 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putendl_fd(char *s, int fd)
{
	char	endl;

	if (!s)
		return ;
	endl = '\n';
	ft_putstr_fd(s, fd);
	write(fd, &endl, 1);
}
