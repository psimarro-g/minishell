# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psimarro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 10:20:49 by psimarro          #+#    #+#              #
#    Updated: 2023/10/03 09:00:25 by psimarro         ###   ########.fr        #
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

CFLAGS		=  -g3 #-fsanitize=address #-Wall -Wextra -Werror -O0
LDFLAGS 	= libft/libft.a #-fsanitize=address
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
SRC 		=	main.c fancy_logo.c init_functions.c envp_utils.c signals.c\
				ms_lstadd_back.c ms_lstlast.c ms_lstnew.c ms_lstdelone.c ms_lstclear.c ms_lstsize.c\
				execute.c execute_utils.c \
				parser.c parse_functions.c parse_env.c  parse_files.c parse_quotes.c parse_pipe.c\
				parse_here_doc.c parse_utils.c parse_utils2.c parse_utils_hd.c\
				echo.c cd.c exit.c pwd.c env.c export.c unset.c minishell.c\

OBJ_DIR		=	obj/
OBJ			= 	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
VPATH 		= 	src/:src/parser/:src/built_ins/:src/lst_utils/:src/execute:

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

bonus:		
	@echo "\n\033[31mNo bonus here! (╯°□°）╯︵ ┻━┻\033[37m\n"

.PHONY:		all libft clean fclean re bonus