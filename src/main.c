/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/16 11:01:59 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	executing = 0;

void	handler(int signo)
{
	//Debug
	printf("Signal %d received\n", signo);
}

void	change_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = &handler;
	sig.sa_flags = SA_RESTART;
	sigfillset(&sig.sa_mask);
	
	sigaction(SIGINT, &sig, NULL);
}

void	ini_shell(t_mshell *mshell, char **envp)
{
	mshell->envp = envp;
	//Tenemos que saber la longuitud del dir para llamar a getcwd, pero no podemos mirarlo bien, habrá que hacer chapuza
	//mshell->cwd = getcwd();
	mshell->exit_status = 0;
	change_signals();
}

int	main (int argc, char **argv, char **envp)
{
	//t_mshell		mshell;
	t_parsemshell	args;
	char			*line;
	int				status;

	(void) argc;
	(void) argv;
	args.parse_list[0] = &parse_command;
	//ini_shell(&mshell, envp);
	status = 0;
	while (1)
	{
		line = readline(GREEN"minishell $> "RESET);
		printf("line: %s\n", line);
		args = parse_line(line, envp);
		//status = execute(args);
		free(line);
		//free(args);
	}
	return (0);
}
