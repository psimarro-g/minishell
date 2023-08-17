/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 08:36:00 by dmontoro          #+#    #+#             */
/*   Updated: 2023/08/17 09:21:02 by dmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_LST_H
# define MS_LST_H

typedef struct s_cmdlist
{
	struct s_cmdlist    *next;
	struct s_cmdlist	*pre;
	char                *cmd;
	char				*path;
    char                **args;
	int					input; //Descriptores de fichero e/s
	int					output;

}	t_cmdlist;

void		ms_lstadd_back(t_cmdlist **lst, t_cmdlist *new);
t_cmdlist	*ms_lstlast(t_cmdlist *lst);



# endif