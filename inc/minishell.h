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
# include "../libft/inc/libft.h"

# define RESET				"\x1b[0m"
# define WHITE				"\x1b[1m"
# define GRAY				"\x1b[2m"
# define BLACK				"\x1b[30m"
# define RED				"\x1b[31m"
# define GREEN				"\x1b[32m"
# define YELLOW				"\x1b[33m"
# define BLUE				"\x1b[34m"
# define PURPLE				"\x1b[35m"
# define CYAN				"\x1b[36m"

# define FUN_SIZE			6

typedef struct s_cmdlist
{
	struct s_cmdlist    *next;
	struct s_cmdlist	*pre;
	char                *cmd;
	char				*path;
    char                **flags; //args y flags? realmente las flags son args no?
    char                **args;
}	t_cmdlist;

//Se podria optimizar usando un int para cada tipo de token y así guardar todas las flags en un entero
typedef struct s_parsemshell
{
	t_cmdlist	*cmds;
	char		**envp;
	int			num_commands;	//un solo comando o pipex
	int			env; 			//variable de entorno $?
	int			built_in;		//built_in funcion
	int			input;			// <
	int			output;			// >
	int			here_doc;		// <<
	int			append_output;	// >>
	int (**parse_list)(struct s_parsemshell *, char *, char *, int *);


}	t_parsemshell;

typedef struct s_mshell
{
	char		**envp;
	char		*cwd;
	int			exit_status;
	int (*parse_list[FUN_SIZE])(struct s_parsemshell *, char *, char *, int *);


}	t_mshell;

/* MAIN.C */
int		rl_replace_line(char *s, int a);
void	rl_redisplay(void);
int		rl_on_new_line(void);
void	ft_add_history(char *read);
void	ft_read_history(void);

/* BUILT_INS/ECHO.C */
void			echo(char **args);

/* FANCY_LOGO.C */
void			fancy_logo(void);

/* PARSER/PARSER.C */
t_parsemshell	parse_line(char *line, char **envp, int (*parse_list[FUN_SIZE])(t_parsemshell *, char *, char *, int *));
char			*get_token(const char *line, int *i);

/* PARSER/PARSE_ENV.C */
char			*expand_var(char *var, char **envp);
int				parse_env(t_parsemshell *args, char *token, char *line, int *i);


/* PARSER/PARSE_HEREDOC.C */
int				parse_here_doc(t_parsemshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_UTILS2.C */
int				check_comillas(char c, const char *s, int i);
int				count_words(char const *s);

/* PARSER/PARSE_UTILS.C*/
char			**split_and_expand(char const *s, int *i, char **envp);
int				parse_command(t_parsemshell *args, char *token, char *line, int *i);
char			**split_args(char const *s);

#endif
