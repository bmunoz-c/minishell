# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:20:48 by ltrevin-          #+#    #+#              #
#    Updated: 2024/10/10 21:47:20 by ltrevin-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g #-fsanitize=address

LIBS 			= -lreadline -Linc/libft -lft
INCLUDE 		= -Iinc 
HEADER			= inc/minishell.h

SRC_DIR 		= src
OBJ_DIR 		= obj
SRC 			= $(SRC_DIR)/main.c
OBJ				= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(NAME) : $(OBJ) | libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libft:
	@$(MAKE) -C inc/libft bonus --no-print-directory

clean :
	rm -rf $(OBJ_DIR)
