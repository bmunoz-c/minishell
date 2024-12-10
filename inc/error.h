/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:00:32 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/10 22:35:08 by borjamc          ###   ########.fr       */
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

#endif
