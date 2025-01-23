/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:00:32 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/23 16:02:06 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define PERM_ERR 1
# define NOFDIR_ERR 1
# define NODIR_ERR 1
# define SYNTAX_ERROR 2

//_____BUILDING_ERRORS_____//
# define PATH_NULL "Path is NULL"
# define INV_PATH "Invalid path"
# define NOFILEDIR "No such file or directory"
# define NOTDIR "Not a directory"
# define PERM_DENIED "Permission denied"
# define WRONG_ARG "Wrong number of arguments"
# define STAT_ERR "Stat function failed"

//_____CMD_ERRORS_____//
# define CMDNOTFND "Command not found"

//_____TOKENIZER_ERRORS_____//
# define NEAR_UN_TOKEN "near unexpexted token "
# define SYNT_ERR_UN_T "dancingShell: syntax error near unexpected token `"
# define QUOTE_FORMAT_ERROR "quotes not closed correctly"

# define FLAG_FOUND "%s %s: %c%c: options are not allowed\n"

# define PROGRAM_NAME "dancingShell🩰🦦:"
# define ECHO "echo"
# define CD "cd"
# define PWD "pwd"
# define EXPORT "export"
# define UNSET "unset"
# define ENV "env"
# define EXIT "exit"

# define IS_DIR 2
# define IS_F_EXEC 1
# define NOT_FOUND 0

#endif
