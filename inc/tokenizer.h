/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/15 20:54:00 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

//ESTRUCTURA ENUMERACION TIPO DE TOKEN
typedef enum e_token_type
{
	WORD,
	SPC,
	PIPE,
	REDIR,
	SQ_STR,
	DQ_STR,
	ENV_VAR,
	//____Redirections_____//
	HERE_DOC,
	INPUT,
	OUTPUT,
	APPEND,
}	t_token_type;

typedef struct s_token
{
	enum e_token_type	type;			//Tipo de token
	char			*content;		//Texto del token
	struct s_token			*next;			//Puntero al siguiente token
	struct s_token			*prev;			//Puntero al anterior token

}	t_token;


typedef struct s_env
{
	char			*key;
	char			*value;
	struct  s_env 	*next;
}	t_env;

typedef struct s_data
{
	t_token		*token_list;		//Puntero a una lista de tokens
	t_env		**env;
	char		**path;
	char		*prompt;
	int			err_code;
	char		*err_msg;

}	t_data;

//_____SYNTAX_____//
int		check_quotes(t_data *data);
int		check_pipe(t_data *data, char *line, int index);
int		check_redirection(t_data *data, char *line, int index);
int		check_syntax(t_data *data);

//_____SYNTAX_UTILS_____//
int		is_redirection(char *line, int index);
void	metachars_error(t_data *data, char *metachars);
int		check_metachar(t_data *data, char *line, int i);

//_____ERRORS_____//
void	metachars_error(t_data *data, char *metachars);
int		syntax_error(t_data *data, char *msg);

#endif
