/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:25:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/22 12:37:45 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


static void	interrupt_handler(int signo)
{
	//Debug
	//printf("Signal %d received\n", signo);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

//Queremos que reciba el handler porque cuando no hay nada en ejecución minishell tiene que printear
//Pero cuando haces sigquit minishell nunca tiene que hacer nada.
void	change_signals(void)
{
	signal(SIGINT, &interrupt_handler);
	signal(SIGQUIT, SIG_IGN);
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
	ft_bzero(mshell, sizeof(t_mshell));
	mshell->envp = envp;
	mshell->cwd = ft_getcwd();
	mshell->exit_status = 0;
	mshell->cmds = ms_lstnew(NULL, NULL, NULL);
	mshell->parse_list[0] = &parse_here_doc;
	mshell->parse_list[1] = &parse_env;
	mshell->parse_list[2] = &parse_pipe;
	mshell->parse_list[3] = &parse_command;
	change_signals();
}