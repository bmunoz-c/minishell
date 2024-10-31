# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:20:48 by ltrevin-          #+#    #+#              #
#    Updated: 2024/10/31 16:51:33 by borjamc          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address

LIBS 			= -lreadline -Linc/libft -lft
INCLUDE 		= -Iinc 
HEADER			= inc/minishell.h

SRC_DIR 		= src/
OBJ_DIR 		= obj/
SRC 			:= main.c clean_utils.c env.c env_utils.c\
				  builtins/echo.c \
				  tokenizer/tokenizer.c tokenizer/token_type.c tokenizer/error_mng.c

SRC				:= $(addprefix $(SRC_DIR), $(SRC))
OBJ				= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

all : $(NAME)

re : fclean all

$(NAME) : $(OBJ) | libft
	echo $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/builtins $(OBJ_DIR)/tokenizer

libft:
	@$(MAKE) -C inc/libft --no-print-directory


clean :
	rm -rf $(OBJ_DIR)

fclean : clean 
	@$(MAKE) -C inc/libft fclean --no-print-directory
	rm $(NAME)

test : 

.PHONY : all clean fclean re
