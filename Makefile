# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:20:48 by ltrevin-          #+#    #+#              #
#    Updated: 2024/10/15 21:36:45 by ltrevin-         ###   ########.fr        #
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
SRC 			:= main.c clean_utils.c env.c\
				  builtins/echo.c \
				  #tokenizer/check_syntax.c tokenizer/syntax_utils.c tokenizer/tokenizer.c
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
