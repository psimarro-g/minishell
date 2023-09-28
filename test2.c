"include"

int	main (void)
{
	char			line[100] = "hola que tal";
	char			line2[100] = "hola que tallllll";

	if (ft_strncmp(line, line2, ft_strlen) == 0)
        printf("son iguales\n");
    else
        printf("son distintos\n");
	status = 0;
	while (1)
	{
		line = readline(GREEN"minishell $> "RESET);
		if (!line) //esto es para poder salir facilmente con ctrl + D
			exit(0);
		//printf("line: %s\n", line);
		parse_line(line, &mshell);
		if(mshell.exit_status == 0)
		//status = execute(args);
		show_cmds(mshell.cmds);
		free(line);
		//free(args);
	}
	return (0);
}
