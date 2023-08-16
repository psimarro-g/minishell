/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:36:14 by psimarro          #+#    #+#             */
/*   Updated: 2023/08/16 11:37:24 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

static void	blue(void)
{
	printf("\033[0;34m");
}

static void	reset(void)
{
	printf("\033[0m");
}

void	fancy_logo(void)
{
	blue();
	printf("   __  __   _____   _   _   _____    _____"
		"   _    _   ______   _        _\n"
		"  |  \\/  | |_   _| | \\ | | |_   _|  / ____| "
		"| |  | | |  ____| | |      | |\n"
		"  | \\  / |   | |   |  \\| |   | |   | (___   "
		"| |__| | | |__    | |      | |\n"
		"  | |\\/| |   | |   | . ` |   | |    \\___ \\"
		"  |  __  | |  __|   | |      | |\n"
		"  | |  | |  _| |_  | |\\  |  _| |_   ____) |"
		" | |  | | | |____  | |____  | |____\n"
		"  |_|  |_| |_____| |_| \\_| |_____| |_____/"
		"  |_|  |_| |______| |______| |______|\n");
	reset();
}
