/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 11:37:20 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	executing = 0;

// const static	int (*parse_list[FUN_SIZE])(struct s_parsemshell *, char *, char *, int *) = {
// 	&parse_env,
// 	&parse_command,
// 	&parse_input,
// 	&parse_output,
// 	&parse_append_output,
// 	&parse_here_doc
// };

void	show_ini_data(t_mshell *mshell)
{
	int	i;

	printf("cwd: %s\n", mshell->cwd);
}

void	show_cmds(t_cmdlist *cmds)
{
	t_cmdlist	*act;
	int			i;

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

int	main (int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	char			*line;
	int				status;

	(void) argc;
	(void) argv;
	mshell.parse_list[0] = &parse_here_doc;
	mshell.parse_list[1] = &parse_env;
	mshell.parse_list[2] = &parse_pipe;
	mshell.parse_list[3] = &parse_command;
	ini_shell(&mshell, envp);
	fancy_logo();
	show_ini_data(&mshell);
	status = 0;
	while (1)
	{
		line = readline(GREEN"minishell $> "RESET);
		if (!line) //esto es para poder salir facilmente con ctrl + D
			exit(0);
		parse_line(line, &mshell);
		if (mshell.exit_status == 0)
		{
			//status = execute(args);
			show_cmds(mshell.cmds);
		}
		free(line);
		//free(args);
	}
	return (0);
}
