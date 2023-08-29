/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:25:05 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/29 11:46:55 by dmontoro         ###   ########.fr       */
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

//Takes the attributes of the terminal
//removes the flag that prints ^char when you press a signal
//and sets the attributes of the terminal to the new ones
void	remove_print_controlc(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	ini_shell(t_mshell *mshell, char **envp)
{
	char	*value;
	ft_bzero(mshell, sizeof(t_mshell));
	mshell->envp = clone_envp(envp);
	mshell->cwd = ft_getcwd();
	mshell->exit_status = 0;
	mshell->cmds = ms_lstnew(NULL, NULL, NULL);
	mshell->parse_list[0] = &parse_here_doc;
	mshell->parse_list[1] = &parse_env;
	mshell->parse_list[2] = &parse_pipe;
	mshell->parse_list[3] = &parse_command;
	remove_print_controlc();
	change_signals();
	
	value = expand_var("$SHLVL", mshell->envp, mshell->exit_status);
	if (value)
	{
		int lvl = ft_atoi(value);
		free(value);
		value = ft_itoa(lvl + 1);
		set_env("SHLVL", value, &mshell->envp);
		free(value);
	}
}