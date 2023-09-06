/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:24:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 08:24:10 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	probar_comandos(t_cmdlist *args, t_mshell *mshell);

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (ft_strncmp(args->cmd, "cd", 2) == 0)
	{
		cd(args->args[1], &mshell->cwd, &mshell->envp);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "env", 3) == 0)
	{
		env(mshell->envp);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "exit", 4) == 0)
	{
		ft_exit(args->args, mshell->exit_status);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "pwd", 3) == 0)
	{
		pwd(mshell->cwd);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "echo", 4) == 0)
	{
		echo(args->args);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "export", 6) == 0)
	{
		export(args->args, &mshell->envp);
		exit(0);
	}
	if (ft_strncmp(args->cmd, "unset", 5) == 0)
	{
		unset(args->args, &mshell->envp);
		exit(0);
	}
	return (0);
}

void	change_fds(t_cmdlist *act, int pipe_fd[2])
{
	if (act->input != -1)
	{
		dup2(act->input, STDIN_FILENO);
		close(act->input);
	}
	if (act->output != -1)
	{
		dup2(act->output, STDOUT_FILENO);
		close(act->output);
	}
	else if (act->next != NULL)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
//Hacemos el cambio de señales para que coja bien las señales
int	get_status(int pid, int size)
{
	int	status;
	
	// while (--size > 0)
	// 	wait(NULL);
	waitpid(pid, &status, 0);
	g_executing = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

//If it gets to execute, it has to have at least 1 good command
/*Execute -> Antes de hacer exec tiene que tener la entrada correcta y la salida correcta y las señales bien
//Entrada puede ser:
	- Stdin (-1)
	- Pipe (-1) sin ser el primer comando
	- Un archivo (> 0)
//La salida puede ser:
	- Stdout (-1)
	- Pipe (-1) sin ser el ultimo comando
	- Un archivo (> 0)
*/
int	execute(t_mshell *mshell)
{
	t_cmdlist	*act;
	pid_t		pid;
	int			pipe_fd[2];
	
	g_executing = 1;
	act = mshell->cmds;
	while (act)
	{
		if (pipe(pipe_fd) == -1)
			ft_error("Error creating pipe", mshell, 1);
		pid = fork();
		if(pid == 0)
		{
			default_signals();
			change_fds(act, pipe_fd);
			if (probar_comandos(act, mshell) == 0)
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
					execve(act->path, act->args, mshell->envp);
				}
			}
		}
		else
		{
			if (act->input != -1)
				close(act->input);
			if (act->output != -1)
				close(act->output);
			if (act->next != NULL)
				act->next->input = pipe_fd[0];
			else
				close(pipe_fd[0]);
			close(pipe_fd[1]);
			act = act->next;
		}
	}
	return (get_status(pid, mshell->num_commands));
}
