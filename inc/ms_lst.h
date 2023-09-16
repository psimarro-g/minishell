/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:36:00 by dmontoro          #+#    #+#             */
/*   Updated: 2023/09/16 12:37:30 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LST_H
# define MS_LST_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_cmdlist
{
	struct s_cmdlist    *next;
	struct s_cmdlist	*pre;
	char				*cmd;
	char				*path;
	char				**args;
	int					input;
	int					output;

}	t_cmdlist;

/* LST_UTILS/ */
void		ms_lstadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*ms_lstlast(t_cmdlist *lst);
t_cmdlist	*ms_lstnew(char *cmd, char *path, char **args);
void		ms_lstdelone(t_cmdlist *lst);
void		ms_lstclear(t_cmdlist **lst);
int			ms_lstsize(t_cmdlist *lst);

# endif
