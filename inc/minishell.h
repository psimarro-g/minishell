#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_cmdlist
{
	struct s_cmdlist    *next;
	struct s_cmdlist	*pre;
	char                *cmd;
    char                **flags;
    char                **args;
}	t_cmdlist;

typedef struct s_mshell
{
	t_cmdlist	*cmds;
	int			pipex;			//un solo comando o pipex
	int			env; 			//variable de entorno $?
	int			built_in;		//built_in funcion
	int			input;			// <
	int			output;			// >
	int			here_doc;		// <<
	int			append_output;	// >>
}	t_mshell;

#endif
