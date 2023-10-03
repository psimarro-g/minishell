/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 06:57:42 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 12:49:55 by dmontoro         ###   ########.fr       */
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

static void	show_ini_data(t_mshell *mshell, char *mshell_path)
{
	int			i;
	char	*mshell_dir;
	char	*aux;

	i = 0;
	mshell_dir = expand_var("$MSHELLDIR", mshell->envp,
						mshell->exit_status);
	if (!mshell_dir)
	{
		if (mshell_path[0] == '/')
			mshell_dir = ft_strdup(mshell_path);
		else
		{
			aux = ft_strjoin("/", mshell_path);
			mshell_dir = ft_strjoin(mshell->cwd, aux);
			mshell_dir = ft_trim_dir(mshell_dir);
			free(aux);
		}
		set_env("MSHELLDIR", mshell_dir, &mshell->envp);
	}
	mshell->mshell_dir = mshell_dir;
	//printf(GREEN"  cwd: %s\n\n"RESET, mshell->cwd);
}

static void	show_cmds(t_cmdlist *cmds)
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

static void	free_commands(t_mshell *mshell)
{
	ms_lstclear(&mshell->cmds);
	mshell->cmds = ms_lstnew(NULL, NULL, NULL);
	mshell->num_commands = 0;
	g_executing = 0;
}
/*
void    show_leaks(void)
{
        system("leaks -q minishell");
}*/

//Tenemos que guardar stdin y stdout para poder restaurarlos
//while : ; do leaks minishell | grep leak; done  -> probar leaks
int	main(int argc, char **argv, char **envp)
{
	t_mshell		mshell;
	char			*line;
	int				free_envp;

	//atexit(show_leaks);
	if (argc != 1 || argv[1] || !envp)
		return (0);
	if (!envp)
	{
		envp = (char **)malloc(sizeof(char *));
		free_envp = 1;
		envp = NULL;
	}
	ini_shell(&mshell, envp);
	//fancy_logo();
	show_ini_data(&mshell, argv[0]);
	rl_clear_history();
	while(1)
	{
		line = readline(GREEN"minishell $> "RESET);
		if (!line)
			ft_exit(NULL, mshell.exit_status);
		if (ft_strlen(line) > 0)
			add_history(line);
		mshell.error = 0;
		parse_line(line, &mshell);
		if (mshell.cmds->cmd && !mshell.error)
		{
			mshell.exit_status = execute(&mshell);
			//show_cmds(mshell.cmds);
		}
		free_commands(&mshell);
		free(line);
	}
	free(mshell.cwd);
	free(mshell.mshell_dir);
	return (0);
}
