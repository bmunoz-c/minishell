# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:20:48 by ltrevin-          #+#    #+#              #
#    Updated: 2024/12/12 16:47:51 by bmunoz-c         ###   ########.fr        #
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
SRC 			:=	main.c clean_utils.c env.c\
					builtins/echo.c builtins/pwd.c\
					tokenizer/tokenizer.c tokenizer/token_type.c\
					executor/executor.c executor/cmd_list.c executor/path_search.c\
					expansor/expansor.c expansor/expansor_utils.c\
					prep_exec/merge_token.c\
					syntax/syntax.c\
					signals/signals.c\
					init_data.c	print_utils.c					
SRC				:= $(addprefix $(SRC_DIR), $(SRC))
OBJ				= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

#_____Colors_____#
DEF_COLOR	=	\033[1;39m
WHITE_BOLD	=	\033[1m
RED			=	\033[1;31m
GREEN		=	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
CIAN		=	\033[1;36m

all : $(NAME)

re : fclean all

$(NAME) : $(OBJ) | libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo "$(RED)$(NAME) $(BLUE)is ready to work!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) | $(OBJ_DIR) libft
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(WHITE_BOLD)Object$(YELLOW) $@ $(GREEN)compiled!$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)builtins $(OBJ_DIR)tokenizer
	@mkdir -p $(OBJ_DIR)expansor $(OBJ_DIR)executor $(OBJ_DIR)prep_exec
	@mkdir -p $(OBJ_DIR)syntax  $(OBJ_DIR)signals
	@echo "$(WHITE_BOLD)Created obj dir!$(DEF_COLOR)"

libft:
	@$(MAKE) -C inc/libft --no-print-directory


clean :
	rm -rf $(OBJ_DIR)

fclean : clean 
	@$(MAKE) -C inc/libft fclean --no-print-directory
	rm -f $(NAME)

test : 

.PHONY : all clean fclean re
