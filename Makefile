# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmontoro <dmontoro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 10:20:49 by psimarro          #+#    #+#              #
#    Updated: 2023/08/17 09:18:56 by dmontoro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME	= minishell

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

CC 		= gcc

CFLAGS	= -g3 -O0 #-Wall -Wextra -Werror -g3
LDFLAGS = libft/libft.a
LIBS 	= -l readline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
RM		= rm -f

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

INC_DIR	= inc/
HEADER	= inc/minishell.h

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_DIR				=	src/
SRC =	main.c	fancy_logo.c\
		ms_lstadd_back.c \
		parser.c parse_functions.c  parse_env.c parse_utils.c parse_utils2.c\
		parse_here_doc.c \
		echo.c

OBJ_DIR				=	obj/
OBJ					= 	$(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
VPATH 				= 	src/:src/parser/:src/built_ins/:src/lst_utils

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: libft $(NAME)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(LIBS) $(OBJ) $(LDFLAGS)
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