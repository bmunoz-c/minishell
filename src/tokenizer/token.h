/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:45:23 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/11 20:06:11 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "../../inc/context.h"

//ESTRUCTURA ENUMERACION TIPO DE TOKEN
typedef enum e_token_type
{
	WORD,
	SPACE,
	PIPE,
	REDIR,
	SQ_STR,
	DQ_STR,
	ENV_VAR

	HERE_DOC,
	INPUT,
	OUTPUT, 
	APPEND,
}	t_token_type;


typedef struct s_token
{
	e_token_type	type;			//Tipo de token
	char			*content;		//Texto del token
	s_token			*next;			//Puntero al siguiente token
}	t_token;

//Puntero a token & cantidad de tokens
typedef struct s_data
{
	t_token		*token_list;			//Puntero a una lista de tokens
	char		**env;
	char		**path;
	char		*prompt;

}	t_data;





t_token	*tokenize(char *line);

#endif
