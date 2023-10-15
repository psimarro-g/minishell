/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:24:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/15 11:44:18 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	execute_simple(t_mshell *mshell)
{
	if (ft_strcmp(mshell->cmds->cmd, "cd") == 0)
		return (cd(&mshell->cmds->args[1], &mshell->cwd, &mshell->envp));
	if (ft_strcmp(mshell->cmds->cmd, "exit") == 0)
		return (ft_exit(mshell->cmds->args, mshell->exit_status));
	if (ft_strcmp(mshell->cmds->cmd, "export") == 0)
		return (export(mshell->cmds->args, &mshell->envp));
	if (ft_strcmp(mshell->cmds->cmd, "unset") == 0)
		return (unset(mshell->cmds->args, &mshell->envp));
	ft_printf_fd(2, "minishell: %s: command not found\n", mshell->cmds->cmd);
	mshell->exit_status = 127;
	return (0);
}

//TODO Pensar si hay que cerrar input y output en el hijo
static void	execute_child(int pipe_fd[2], t_cmdlist	*act, t_mshell *mshell)
{
	if (act->error == 1 || act->cmd == NULL)
		exit(mshell->exit_status);
	if (!built_in(act->cmd) && act->path == NULL)
	{
		if (is_directory(act->cmd) && \
			(!ft_strncmp(act->cmd, "./", 2) || !ft_strncmp(act->cmd, "/", 1)))
		{
			ft_printf_fd(2, "minishell: %s: is a directory\n", act->cmd);
			exit(126);
		}
		ft_printf_fd(2, "minishell: %s: command not found\n", act->cmd);
		exit(127);
	}
	default_signals();
	change_fds(act, pipe_fd);
	if (probar_comandos(act, mshell) == 0)
	{
		if (execve(act->path, act->args, mshell->envp) == -1)
			exit(126);
	}
}

static void	manage_parent_fds(t_cmdlist	*act, int pipe_fd[2])
{
	if (act->input != -1)
		close(act->input);
	if (act->output != -1)
		close(act->output);
	if (act->next != NULL && act->next->input == -1)
		act->next->input = pipe_fd[0];
	else
		close(pipe_fd[0]);
	close(pipe_fd[1]);
}

//If it gets to execute, it has to have at least 1 good command
/*Execute -> Antes de hacer exec tiene que tener la entrada 
correcta y la salida correcta y las señales bien
Entrada puede ser:
	- Stdin (-1)
	- Pipe (-1) sin ser el primer comando
	- Un archivo (> 0)
La salida puede ser:
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
		if (pid == -1)
			ft_error("Error creating fork", mshell, 1);
		if (pid == 0)
			execute_child(pipe_fd, act, mshell);
		else
		{
			manage_parent_fds(act, pipe_fd);
			act = act->next;
		}
	}
	return (get_status(pid, mshell->exit_status));
}

int	execute(t_mshell *mshell)
{
	if (is_simple(mshell))
		return (execute_simple(mshell));
	return (execute_pipes(mshell));
}
