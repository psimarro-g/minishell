#include "../../inc/minishell.h"

void	cd(char *path, char **cwd, char **envp)
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
		set_env("OLDPWD", *cwd, &envp);
		free(*cwd);
		*cwd = tmp;
	}
	printf("DEBUG: Function cd: PWD Despues del cambio: %s\n", *cwd);
	set_env("PWD", *cwd, &envp);
}