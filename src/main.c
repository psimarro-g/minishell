/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/29 11:05:41 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_executing = 0;

void	show_ini_data(t_mshell *mshell)
{
	int	i;

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

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (strcmp(args->cmd, "cd") == 0)
	{
		cd(args->args[1], &mshell->cwd, &mshell->envp);
		return (1);
	}
	if (strcmp(args->cmd, "env") == 0)
	{
		env(mshell->envp);
		return (1);
	}
	if (strcmp(args->cmd, "exit") == 0)
	{
		ft_exit(args->args, mshell->exit_status);
		return (1);
	}
	if (strcmp(args->cmd, "pwd") == 0)
	{
		pwd(mshell->cwd);
		return (1);
	}
	if (strcmp(args->cmd, "echo") == 0)
	{
		echo(args->args);
		return (1);
	}
	if (strcmp(args->cmd, "export") == 0)
	{
		export(args->args, &mshell->envp);
		return (1);
	}
	if (strcmp(args->cmd, "unset") == 0)
	{
		unset(args->args, &mshell->envp);
		return (1);
	}

	return (0);
}

//If it gets to execute, it has to have at least 1 good command
int	execute(t_mshell *mshell)
{
	t_cmdlist	*act;
	int			i;
	int			pid;

	//restauramos los fds
	act = mshell->cmds;
	while (act)
	{
		//clonar fds correspondientes
		//hacer fork
		//execute cada comando normal
		pid = fork();
		if (pid == 0)
		{
			act = act->next;
			continue ;
		}
		if (probar_comandos(act, mshell) != 0)
			return (0);
		
		if (act->path == NULL)
		{
			printf("minishell: %s: command not found\n", act->cmd);
			mshell->exit_status = 127;
		}
		else
		{
			printf("DEBUG: Function execute: executing %s\n", act->cmd);
			g_executing = 1;
			execve(act->path, act->args, mshell->envp);
		}
	}
	return (0);
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
		if (mshell.exit_status == 0)
		{
			mshell.exit_status = execute(&mshell);
			//probar_comandos(mshell.cmds, &mshell);
			show_cmds(mshell.cmds);
		}
		free_commands(&mshell);
		free(line);
		//line = strdup("pwd");
	}
	free(mshell.cwd);
	return (0);
}
