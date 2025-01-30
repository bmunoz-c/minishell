# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/10 21:20:48 by ltrevin-          #+#    #+#              #
#    Updated: 2025/01/30 02:51:13 by jsebasti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= minishell
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=address

# Para trabajar con readline, instala con:
#   > brew install readline
# Y comenta y descomenta las variables de
# LIBS e INCLUDE dependiendo del sistema en el que estes

# LINUX
LIBS 			= -lreadline -Linc/libft -lft
INCLUDE 		= -Iinc 
# MACOS
#LIBS 			= -L/usr/local/opt/readline/lib -lreadline -Linc/libft -lft
#INCLUDE 		= -Iinc -I/usr/local/opt/readline/include


HEADER			= inc/minishell.h inc/structs.h inc/error.h inc/tokenizer.h

SRC_DIR 		= src/
OBJ_DIR 		= obj/
SRC 			:=	main.c \
					builtins/echo.c builtins/pwd.c builtins/exit.c builtins/export.c builtins/export_utils.c\
					builtins/env.c builtins/unset.c builtins/cd.c builtins/utils.c\
					tokenizer/tokenizer.c tokenizer/token_type.c tokenizer/merge_token.c\
					executor/exeggutor.c executor/cmd_list.c executor/path_search.c executor/pipes.c executor/utils.c executor/utils2.c\
					expansor/expansor.c expansor/expansor_utils.c\
					syntax/syntax.c signals/signals.c\
					utils/init_data.c utils/clean_utils.c\
					utils/env_utils.c utils/env_matrix_utils.c utils/clean_utils_2.c\
					heredoc/heredoc.c
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

LIBFT_EXEC = inc/libft/libft.a
all : $(NAME)

re : fclean all

$(NAME) : $(OBJ) $(LIBFT_EXEC) | libft
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBS)
	@echo "$(RED)$(NAME) $(BLUE)is ready to work!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile $(LIBFT_EXEC) | $(OBJ_DIR) libft
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(WHITE_BOLD)Object$(YELLOW) $@ $(GREEN)compiled!$(DEF_COLOR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)builtins $(OBJ_DIR)tokenizer
	@mkdir -p $(OBJ_DIR)expansor $(OBJ_DIR)executor $(OBJ_DIR)heredoc
	@mkdir -p $(OBJ_DIR)syntax  $(OBJ_DIR)signals $(OBJ_DIR)utils
	@echo "$(WHITE_BOLD)Created obj dir!$(DEF_COLOR)"

libft: $(LIBFT_EXEC)

$(LIBFT_EXEC):
	@$(MAKE) -C inc/libft --no-print-directory

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean 
	@$(MAKE) -C inc/libft fclean --no-print-directory
	@rm -f $(NAME)

test : 

.PHONY : all clean fclean re
