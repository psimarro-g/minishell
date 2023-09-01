/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:15:41 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/01 11:09:47 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	interrupt_handler(int signo)
{
	//Debug
	//printf("Debug: Function interrupt_handler: %d received\n", signo);
	if (g_executing == 0)
	{
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
	}
	else if (g_executing == 1)
	{
		close(0);
		printf("\n");
		g_executing = 0;
	}
}

//Queremos que reciba el handler porque cuando no hay nada en ejecución minishell tiene que printear
//Pero cuando haces sigquit minishell nunca tiene que hacer nada.
void	change_signals(void)
{
	signal(SIGINT, &interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}