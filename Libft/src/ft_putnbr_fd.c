/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:52:31 by psimarro          #+#    #+#             */
/*   Updated: 2022/06/08 16:52:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nn;

	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nn = nb * -1;
	}
	else
		nn = nb;
	if (nn >= 10)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putchar_fd((nn % 10) + '0', fd);
	}
	else if (nn >= 0 && nn <= 9)
	{
		ft_putchar_fd(nn + '0', fd);
	}
}
