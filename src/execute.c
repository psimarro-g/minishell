/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:24:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/06 09:37:41 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	probar_comandos(t_cmdlist *args, t_mshell *mshell);

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (ft_strncmp(args->cmd, "cd", ft_strlen(args->cmd)) == 0)
		exit(cd(args->args[1], &mshell->cwd, &mshell->envp));
	if (ft_strncmp(args->cmd, "env", ft_strlen(args->cmd)) == 0)
		exit(env(mshell->envp));
	if (ft_strncmp(args->cmd, "exit", ft_strlen(args->cmd)) == 0)
		exit(ft_exit(args->args, mshell->exit_status));
	if (ft_strncmp(args->cmd, "pwd", ft_strlen(args->cmd)) == 0)
		exit(pwd(mshell->cwd));
	if (ft_strncmp(args->cmd, "echo", ft_strlen(args->cmd)) == 0)
		exit(echo(args->args));
	if (ft_strncmp(args->cmd, "export", ft_strlen(args->cmd)) == 0)
		exit(export(args->args, &mshell->envp));
	if (ft_strncmp(args->cmd, "unset", ft_strlen(args->cmd)) == 0)
		exit(unset(args->args, &mshell->envp));
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

static int	is_simple(t_mshell *mshell)
{
	return (mshell->num_commands == 1 && (ft_strncmp(mshell->cmds->cmd, "cd", ft_strlen(mshell->cmds->cmd)) == 0
		|| ft_strncmp(mshell->cmds->cmd, "exit", ft_strlen(mshell->cmds->cmd)) == 0
		|| ft_strncmp(mshell->cmds->cmd, "export", ft_strlen(mshell->cmds->cmd)) == 0
		|| ft_strncmp(mshell->cmds->cmd, "unset", ft_strlen(mshell->cmds->cmd)) == 0));
}

static int	execute_simple(t_mshell *mshell)
{

	if (ft_strncmp(mshell->cmds->cmd, "cd", 2) == 0)
		return (cd(mshell->cmds->args[1], &mshell->cwd, &mshell->envp));
	if (ft_strncmp(mshell->cmds->cmd, "exit", 4) == 0)
		return (ft_exit(mshell->cmds->args, mshell->exit_status));
	if (ft_strncmp(mshell->cmds->cmd, "export", 6) == 0)
		return (export(mshell->cmds->args, &mshell->envp));
	if (ft_strncmp(mshell->cmds->cmd, "unset", 5) == 0)
		return (unset(mshell->cmds->args, &mshell->envp));
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
static int	execute_pipes(t_mshell *mshell)
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

int	execute(t_mshell *mshell)
{
	if (is_simple(mshell))
		return (execute_simple(mshell));
	return (execute_pipes(mshell));
}
