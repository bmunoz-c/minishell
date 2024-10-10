/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:45:23 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 22:07:08 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

#include "../../inc/context.h"

//ESTRUCTURA ENUMERACION TIPO DE TOKEN
typedef enum e_token_type
{
	CMD,
	PIPE,
	DEF,
}	t_token_type;

//ESTRUCTURA ENUMERACION REDIRECCIONES
typedef enum e_redirection
{
	HERE_DOC,
	INPUT,
	OUTPUT, 
	APPEND,
	UKNOWN,
}	t_redirection;

typedef struct s_token
{
	t_token_type	type;			//Tipo de token
	char			*txt_token		//Texto del token
	char			**av;			//Lista de argumentos
	int				ac;				//Cantidad de argumentos
	t_redirection	*redirections;	//Info sobre redirecciones

	int				here_docs		//Numero de <<
	int				infiles			//Numero de <
	int				ourfiles		//Numero de >

	t_token			*next;			//Puntero al siguiente token
	t_tokens		tokens;			//Estructura de tokens
}	t_token;

//Puntero a token & cantidad de tokens
typedef struct s_tokens
{
	t_token	*token;					//Puntero a una t_token
	int		amount;					//Cantidad de tokens
}	t_tokens;





t_token	*tokenize(char *line);

#endif
