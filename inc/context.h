/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:18:20 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/07 20:31:17 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 258

# define CMDNOTFND "command not found"
# define NOFILEDIR "No such file or directory"
# define ISDIRECTORY "is a directory"

typedef struct s_context
{
	int		error_code;
	t_env	local_env
	t_env	global_env;
}	t_context;

#endif
