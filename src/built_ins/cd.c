#include "../../inc/minishell.h"

void	cd(char *path, char *cwd, char **envp)
{
	char	*tmp;

	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return ;
	}
	tmp = ft_getcwd();
	if (tmp)
	{
		free(cwd);
		cwd = tmp;
	}
	set_env("PWD", cwd, &envp);
}