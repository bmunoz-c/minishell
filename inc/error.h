/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:00:32 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/10 21:58:01 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H
# define PERM_ERR 126
# define NOFDIR_ERR 127
# define SYNTAX_ERROR 2

//_____BUILDING_ERRORS_____//
# define PATH_NULL "cd: Path is NULL"
# define INV_PATH "cd: Invalid path"
# define NOFILEDIR "cd: No such file or directory"
# define NOTDIR "cd: Not a directory"
# define PERM_DENIED "cd: Permission denied"

//_____CMD_ERRORS_____//
# define CMDNOTFND "Command not found"

//_____TOKENIZER_ERRORS_____//
# define NEAR_UN_TOKEN "near unexpexted token "
# define QUOTE_FORMAT_ERROR	"quotes not closed correctly"

#endif
