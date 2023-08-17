/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:25:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 11:39:02 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


void	handler(int signo)
{
	//Debug
	//printf("Signal %d received\n", signo);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

void	change_signals(void)
{
	struct sigaction	sig;

	sig.sa_handler = &handler;
	sig.sa_flags = SA_RESTART;
	sigfillset(&sig.sa_mask);
	
	sigaction(SIGINT, &sig, NULL);
}

char	*ft_getcwd()
{
	char *ret;

	ret = malloc(sizeof(char) * PATH_MAX);
	if(getcwd(ret, PATH_MAX) != NULL)
		return (ret);
	return (NULL);
}

void	ini_shell(t_mshell *mshell, char **envp)
{
	mshell->envp = envp;
	mshell->cwd = ft_getcwd();
	mshell->exit_status = 0;
	mshell->cmds = ms_lstnew(NULL, NULL, NULL);
	change_signals();
}