/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:37:38 by psimarro          #+#    #+#             */
/*   Updated: 2023/10/03 12:47:31 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/inc/libft.h"
# include "ms_lst.h"

# define RESET		"\x1b[0m"
# define WHITE		"\x1b[1m"
# define GRAY		"\x1b[2m"
# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define PURPLE		"\x1b[35m"
# define CYAN		"\x1b[36m"

# define FUN_SIZE	6

# ifndef PATH_MAX
#  define PATH_MAX	4096
# endif

extern int	g_executing;

typedef struct s_mshell
{
	t_cmdlist	*cmds;
	char		**envp;
	char		*cwd;
	char		*mshell_dir;
	int			num_commands;
	int			last_pid;
	int			exit_status;
	int			error;
	int			(*parse_list[FUN_SIZE])(struct s_mshell *, \
					char *, char *, int *);
}	t_mshell;

/* MAIN.C */
# ifdef __APPLE__
void			rl_replace_line(char *s, int a);
void			rl_redisplay(void);
int				rl_on_new_line(void);
int				add_history(const char *read);
void			rl_clear_history(void);
# endif

/* INIT_FUNCTIONS.C*/
void			ini_shell(t_mshell *mshell, char **envp);
char			*ft_getcwd(void);

/* SIGNALS.C */
void			change_signals(void);
void			default_signals(void);
void			here_doc_signals(void);
void			ignore_signals(void);

/* ENVP_UTILS.C */
void			set_env(char *env, char *value, char ***envp);
char			**add_new_var(char **envp, char *new_var);
char			**delete_var(char **envp, char *key);
char			**clone_envp(char **envp);

/* FANCY_LOGO.C */
void			fancy_logo(void);

/* BUILT_INS/CD.C */
int				cd(char **path, char **cwd, char ***envp);

/* BUILT_INS/ECHO.C */
int				echo(char **args);

/* BUILT_INS/PWD.C */
int				pwd(char *cwd);

/* BUILT_INS/ENV.C */
int				env(char **envp);

/* BUILT_INS/EXPORT.C */
int				export(char **args, char ***envp);

/* BUILT_INS/UNSET.C */
int				unset(char **args, char ***envp);

/* BUILT_INS/EXIT.C */
int				ft_exit(char **args, int exit_status);

/* BUILT_INS/MINISHELL.C */
int				minishell(t_mshell *mshell, char *path, char ***envp);
char			*ft_trim_dir(char *mshell_dir);

/* EXECUTE/EXECUTE.C */
int				execute(t_mshell *mshell);

/* EXECUTE/EXECUTE_UTILS.C*/
int				probar_comandos(t_cmdlist *args, t_mshell *mshell);
void			change_fds(t_cmdlist *act, int pipe_fd[2]);
int				get_status(int pid, int size, int exit_status);
int				is_simple(t_mshell *mshell);
int				built_in(char *cmd);

/* PARSER/PARSER.C */
void			parse_line(char *line, t_mshell *mshell);

/* PARSER/PARSE_ENV.C */
char			*expand_var(char *var, char **envp, int exit_status);
int				parse_env(t_mshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_FILES.C*/
int				parse_files(t_mshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_FUNCTIONS.C*/
int				parse_command(t_mshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_HEREDOC.C */
int				parse_here_doc(t_mshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_PIPE.C*/
int				parse_pipe(t_mshell *args, char *token, char *line, int *i);

/* PARSER/PARSE_QUOTES.C*/
char			*get_tranche(t_mshell *mshell, const char *line, int *i);
int				check_dquotes(const char *line, int i);
char			*ft_strjoin_free(char *s1, char *s2);
char			*get_var(const char *line, int *i);
char			*get_single_quotes(const char *line, int *i);

/* PARSER/PARSE_UTILS_HD.C*/
int				get_eof(char **eof, char *line, int *i);
void			expand_heredoc(t_mshell *mshell, int fd[2], char *line, int expand);

/* PARSER/PARSE_UTILS.C*/
void			ft_error(char *s, t_mshell *mshell, int exit_code);
void			syntax_error(t_mshell *args, char *eof, char *line, int *i);
char			**split_and_expand(char const *s, int *i, t_mshell mshell, char *token);

/* PARSER/PARSE_UTILS2.C */
void			cpy_lst(char **to, char **from, int start);
int				is_token(const char *s, int i);
int				check_comillas(char c, const char *s, int i);
int				count_words(char const *s);
void			check_path(t_cmdlist **act, char *path);

#endif
