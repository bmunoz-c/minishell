/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:19:52 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/24 13:42:41 by ltrevin-         ###   ########.fr       */
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

void copy_env(char **org_env, t_data *data);

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

///////////// ENVIROMENT
void copy_env(char **org_env, t_data *data);
void print_env(t_env *env);
void	*ft_memdel(void *ptr);
void free_env(t_env *env);
/// utils
char *get_env_value(t_env *env, char *key);



#endif
