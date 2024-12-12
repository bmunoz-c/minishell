/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:00:32 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/12 20:51:15 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 2

//_____BUILDING_ERRORS_____//
# define PATH_NULL "Path is NULL"
# define INV_PATH "Invalid path"
# define NOFILEDIR "No such file or directory"
# define NOTDIR "Not a directory"
# define PERM_DENIED "Permission denied"

//_____CMD_ERRORS_____//
# define CMDNOTFND "Command not found"

//_____TOKENIZER_ERRORS_____//
# define NEAR_UN_TOKEN "near unexpexted token "
# define QUOTE_FORMAT_ERROR	"quotes not closed correctly"

# define PROGRAM_NAME "minishell:"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

#endif
