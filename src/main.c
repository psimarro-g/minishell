/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/30 13:19:54 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (ft_strncmp(args->cmd, "cd", 2) == 0)
	{
		cd(args->args[1], &mshell->cwd, &mshell->envp);
		return (1);
	}
	if (ft_strncmp(args->cmd, "env", 3) == 0)
	{
		env(mshell->envp);
		return (1);
	}
	if (ft_strncmp(args->cmd, "exit", 4) == 0)
	{
		ft_exit(args->args, mshell->exit_status);
		return (1);
	}
	if (ft_strncmp(args->cmd, "pwd", 3) == 0)
	{
		pwd(mshell->cwd);
		return (1);
	}
	if (ft_strncmp(args->cmd, "echo", 4) == 0)
	{
		echo(args->args);
		return (1);
	}
	if (ft_strncmp(args->cmd, "export", 6) == 0)
	{
		export(args->args, &mshell->envp);
		return (1);
	}
	if (ft_strncmp(args->cmd, "unset", 5) == 0)
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
	int			pid;

	//restauramos los fds
	//clonar fds correspondientes
	//hacer fork
	//execute cada comando normal

	act = mshell->cmds;
	if (mshell->num_commands == 1)
	{
		if(probar_comandos(mshell->cmds, mshell) != 0)
			return (0);
		pid = fork();
		mshell->last_pid = pid;
		if(pid == 0)
		{
			if (act->path == NULL)
			{
				printf("minishell: %s: command not found\n", act->cmd);
				mshell->exit_status = 127;
				exit(127);
			}
			else
			{
				printf("DEBUG: Function execute: executing %s\n", act->cmd);
				g_executing = 1;
				execve(act->path, act->args, mshell->envp);
			}
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
		//line = ft_strdup("ls");
		if (!line)
			ft_exit(NULL, mshell.exit_status);
		add_history(line);
		parse_line(line, &mshell);
		if (mshell.exit_status == 0)
		{
			mshell.exit_status = execute(&mshell);
			//probar_comandos(mshell.cmds, &mshell);
			waitpid(mshell.last_pid, &mshell.exit_status, 0);
			show_cmds(mshell.cmds);
		}
		free_commands(&mshell);
		free(line);
		//line = strdup("pwd");
	}
	free(mshell.cwd);
	return (0);
}
