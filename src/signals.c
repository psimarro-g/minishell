/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:15:41 by dmontoro          #+#    #+#             */
/*   Updated: 2024/02/01 21:16:46 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	interrupt_handler(int signo)
{
	(void)signo;
	if (g_executing == 0)
	{
		rl_on_new_line();
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*
Queremos que reciba el handler porque cuando no hay nada en ejecución,
minishell tiene que printear.
Pero cuando haces sigquit minishell nunca tiene que hacer nada.
*/
void	change_signals(void)
{
	signal(SIGINT, &interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	here_doc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
