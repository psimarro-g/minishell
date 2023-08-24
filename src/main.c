/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/22 14:42:03 by dmontoro         ###   ########.fr       */
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

	while(1)
	{
		//line = readline(GREEN"minishell $> "RESET);
		line = "..";
		if (!line)
			exit(0);

		cd(line, mshell.cwd, mshell.envp);
		pwd(mshell.cwd);
		continue ;

		parse_line(line, &mshell);
		if (mshell.exit_status == 0)
		{
			//status = execute(args);
			show_cmds(mshell.cmds);
		}
		free_commands(&mshell.cmds);
		free(line);
	}
	free(mshell.cwd);
	return (0);
}
