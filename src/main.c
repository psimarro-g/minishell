/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 07:48:21 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
	-Hay que poner las señales en modo default antes de hacer fork
	-Hay que poner las antiguas al acabar la ejecución
	-Hay que dejar los fds como estaban antes de hacer fork y despues
	-Señal de salida: 
		- 0 si todo ha ido bien
		- <128 si el programa ha acabado con algun error
		- 128 + n si el programa ha acabado por una señal
*/


int	g_executing = 0;

void	show_ini_data(t_mshell *mshell)
{
	printf("cwd: %s\n", mshell->cwd);
}

void	show_cmds(t_cmdlist *cmds)
{
	t_cmdlist	*act;
	int			i;

	if (!cmds->cmd)
		return ;
	act = cmds;
	while (act)
	{
		printf("cmd: %s ", act->cmd);
		printf("path: %s ", act->path);
		printf("args: ");
		i = 0;
		while (act->args[i] != NULL)
		{
			printf("%s ", act->args[i]);
			i++;
		}
		printf("\n");
		act = act->next;
	}
}

void	free_commands(t_mshell *mshell)
{
	ms_lstclear(&mshell->cmds);
	mshell->cmds = ms_lstnew(NULL, NULL, NULL);
	mshell->num_commands = 0;
	g_executing = 0;
}

//Tenemos que guardar stdin y stdout para poder restaurarlos
//while : ; do leaks minishell | grep leak; done  -> probar leaks
int	main(int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	char			*line;

	if (argc != 1 || argv[1] || !envp)
		return (0);
	ini_shell(&mshell, envp);
	fancy_logo();
	show_ini_data(&mshell);

	//line = ft_strdup("cd ..");
	rl_clear_history();
	while(1)
	{
		line = readline(GREEN"minishell $> "RESET);
		if (!line)
			ft_exit(NULL, mshell.exit_status);
		add_history(line);
		parse_line(line, &mshell);
		if (mshell.cmds->cmd)
		{
			mshell.exit_status = execute(&mshell);
			//show_cmds(mshell.cmds);
		}
		free_commands(&mshell);
		free(line);
	}
	free(mshell.cwd);
	return (0);
}
