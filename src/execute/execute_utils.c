/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 09:42:15 by dmontoro          #+#    #+#             */
/*   Updated: 2023/10/03 09:32:09 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	probar_comandos(t_cmdlist *args, t_mshell *mshell)
{
	if (ft_strcmp(args->cmd, "cd") == 0)
		exit(cd(&args->args[1], &mshell->cwd, &mshell->envp));
	if (ft_strcmp(args->cmd, "env") == 0)
		exit(env(mshell->envp));
	if (ft_strcmp(args->cmd, "exit") == 0)
		exit(ft_exit(args->args, mshell->exit_status));
	if (ft_strcmp(args->cmd, "pwd") == 0)
		exit(pwd(mshell->cwd));
	if (ft_strcmp(args->cmd, "echo") == 0)
		exit(echo(args->args));
	if (ft_strcmp(args->cmd, "export") == 0)
		exit(export(args->args, &mshell->envp));
	if (ft_strcmp(args->cmd, "unset") == 0)
		exit(unset(args->args, &mshell->envp));
	if (ft_strcmp(args->cmd, "minishell") == 0)
		exit(minishell(mshell, mshell->mshell_dir, &mshell->envp));
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
int	get_status(int pid, int num_commands)
{
	int	status;

	ignore_signals();
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1) ;
	change_signals();
	g_executing = 0;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int	is_simple(t_mshell *mshell)
{
	return (mshell->num_commands == 1 && (ft_strcmp(mshell->cmds->cmd, "cd") == 0
		|| ft_strcmp(mshell->cmds->cmd, "exit") == 0
		|| ft_strcmp(mshell->cmds->cmd, "export") == 0
		|| ft_strcmp(mshell->cmds->cmd, "unset") == 0));
}

int	built_in(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "minishell") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0);
}