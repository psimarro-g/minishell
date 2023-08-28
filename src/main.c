/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/28 11:16:01 by psimarro         ###   ########.fr       */
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

void	free_commands(t_cmdlist **cmds)
{
	ms_lstclear(cmds);
	*cmds = ms_lstnew(NULL, NULL, NULL);
}

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (strcmp(args->cmd, "cd") == 0)
	{
		cd(args->args[1], &mshell->cwd,mshell->envp);
		return (1);
	}
	if (strcmp(args->cmd, "env") == 0)
	{
		env(mshell->envp);
		return (1);
	}
	if (strcmp(args->cmd, "exit") == 0)
	{
		ft_exit();
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

	return (0);
}

//while : ; do leaks minishell | grep leak; done  -> probar leaks
int	main(int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	char			*line;
	int				status;
	
	if (argc != 1 || argv[1] || !envp)
		return (0);
	ini_shell(&mshell, envp);
	fancy_logo();
	show_ini_data(&mshell);
	status = 0;

	//line = ft_strdup("cd ..");
	while(1)
	{
		line = readline(GREEN"minishell $> "RESET);
		if (!line)
			exit(0);

		parse_line(line, &mshell);
		if (mshell.exit_status == 0)
		{
			//status = execute(args);
			probar_comandos(mshell.cmds, &mshell);
			show_cmds(mshell.cmds);
		}
		free_commands(&mshell.cmds);
		free(line);
		//line = strdup("pwd");
	}
	free(mshell.cwd);
	return (0);
}
