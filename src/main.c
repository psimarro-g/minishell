#include "minishell.h"

int	executing = 0;

int	main (void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (1)
	{
		ft_putstr_fd("minishell$ ", 1);
		line = readline("Prueba");
		args = split_line(line);
		status = execute(args);
		free(line);
		free(args);
	}
	return (0);
}
