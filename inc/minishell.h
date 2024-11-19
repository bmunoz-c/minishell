/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:19:52 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/19 00:52:04 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "tokenizer.h"
#include "error.h"
#include "executor.h"
#include <string.h>
#include <sys/stat.h>
// COLOR MACROS
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#define PROMPT MAGENTA "dancingShell🩰🦦" BLUE "> " RESET 


///////////// INIT STRUCTS
void    init_data(t_data *data);
void	init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last);


///////////// ENVIROMENT
void copy_env(char **org_env, t_data *data);
void free_env(t_env *env);
char *get_env_value(t_env *env, char *key);


//////////// INIT STRUCTS
void	init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last);
void    init_data(t_data *data);

//////////// FREE utils
void	*free_ptr(void *ptr);
void	*free_cmd(t_cmd *cmd);
void    free_cmds(t_cmd *cmd_list);
void	free_env(t_env *env);
void	free_tokens(t_token *token_list);
void	free_token(t_token *token);
void	free_data(t_data *data, int env_flag);
#endif


////////// BUG: Print utils, delete before submit
void print_env(t_env *env);
void	print_cmd(t_cmd *cmd);