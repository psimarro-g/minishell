/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 11:24:45 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/01 12:47:47 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	change_fds(t_cmdlist *act, int pipe_fd[2], int og_fd[2])
{

	if (act->input != -1)
	{
		dup2(act->input, STDIN_FILENO);
		close(act->input);
	}
	if (act->next && act->input == -1)
	{
		dup2(pipe_fd[0], STDIN_FILENO);
	}
	if (act->output == -1)
	{
		dup2(og_fd[1], STDOUT_FILENO);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

int	get_status(int pid)
{
	int	status;
	char *s;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

//If it gets to execute, it has to have at least 1 good command
int	execute(t_mshell *mshell)
{
	t_cmdlist	*act;
	int			pid;
	int			pipe_fd[2];
	
	dup2(STDIN_FILENO, mshell->fd[0]);
	dup2(STDOUT_FILENO, mshell->fd[1]);
	act = mshell->cmds;
	while (act)
	{
		pipe(pipe_fd);
		pid = fork();
		if(pid == 0)
		{
			default_signals();
			change_fds(act, pipe_fd, mshell->fd);
			if(probar_comandos(act, mshell) != 0)
				exit(0);
			if (act->path == NULL)
			{
				printf("minishell: %s: command not found\n", act->cmd);
				exit(127);
			}
			else
			{
				printf("DEBUG: Function execute: executing %s\n", act->cmd);
				g_executing = 1;
				execve(act->path, act->args, mshell->envp);
			}
		}
		else
		{
			if (act->next != NULL)
				dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[1]);
			close(pipe_fd[0]);
			act = act->next;
		}
	}
	close(STDIN_FILENO);
	//coger codigo salida
	return (get_status(pid));
}
