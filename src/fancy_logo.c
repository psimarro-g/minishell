/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fancy_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:36:14 by psimarro          #+#    #+#             */
/*   Updated: 2023/09/19 13:41:49 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void	green(void)
{
	printf("\x1b[32m");
}

static void	reset(void)
{
	printf("\033[0m");
}

void	fancy_logo(void)
{
	green();
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
		"  |_|  |_| |______| |______| |______|\n\n"
		"  .......................... by dmontoro & psimarro"
		" ...........................\n\n");
	reset();
}
