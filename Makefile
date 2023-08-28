# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 10:20:49 by psimarro          #+#    #+#              #
#    Updated: 2023/08/28 13:25:10 by psimarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME		= minishell

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

CC 			= gcc

CFLAGS		= -g3 -ggdb#-Wall -Wextra -Werror -g3
LDFLAGS 	= libft/libft.a
LIBS 		= -l readline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
LIBS_LINUX	= -l readline -L /usr/include/readline -I /usr/include/readline
RM			= rm -f

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

INC_DIR		= inc/
HEADER		= inc/minishell.h

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_DIR		=	src/
SRC 		=	main.c fancy_logo.c init_functions.c envp_utils.c\
				ms_lstadd_back.c ms_lstlast.c ms_lstnew.c ms_lstdelone.c ms_lstclear.c\
				parser.c parse_functions.c parse_env.c parse_utils.c parse_utils2.c\
				parse_here_doc.c parse_pipe.c\
				echo.c cd.c exit.c pwd.c env.c\

OBJ_DIR		=	obj/
OBJ			= 	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
VPATH 		= 	src/:src/parser/:src/built_ins/:src/lst_utils/:

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: libft $(NAME)

linux : libft $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBS_LINUX)  
	@echo "\n\033[32mCompiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) $(LDFLAGS)
	@echo "\n\033[32mCompiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

libft:
	@$(MAKE) -C libft

clean:
	@$(RM) -rf $(OBJ_DIR)
	@$(MAKE) -C libft clean

fclean:				clean
	@$(RM) $(NAME)
	@$(MAKE) -C libft fclean
	@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\033[37m\n"

re:			fclean all

bonus:		re

.PHONY:		all libft clean fclean re bonus