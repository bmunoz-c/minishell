/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/22 18:31:26 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

/*
//_____DEFINES_____//
# define SPACES				0 // Espacios
# define STR				1 // Strinf sin comillas
# define STRSQ				2 // String con comillas simples
# define STRDQ				3 // String con comillas dobles
# define MCH_PIPE			4 // Pipe |
# define REDIR_HDOC			5 // Redir Heredoc <<
# define REDIR_OUT			6 // Redir Output >
# define REDIR_IN			7 // Redir Input <
# define REDIR_APPEND		8 // RedirAppend >>
*/

//_____ENVIRONMENT_STRUCT_____//
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

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

//_____TOKEN_STRUCT_____//
typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	int					expanded;
	struct s_token		*next;
	struct s_token		*prev;

}	t_token;

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
int			check_quotes(t_data *data);
int			check_syntax(t_data *data);

//_____ERRORS_____//
int			syntax_error(t_data *data, char *msg);

//_____TOKENIZER_____//
//_____add_new_token_____//
int			tokenizer(t_data *data, int i);
t_token		*new_token(char *_content, t_token_type _type);
void		add_token(t_token **token_list, t_token *new_token);
void		print_token(t_token *token);
void		print_token_list(t_token *token_list);
//_____token_type_____//
t_token		*sp_token(char *prompt, int	*index);
t_token		*meta_token(char *prompt, int *index);
t_token		*quote_token(char *prompt, int *index, t_token_type type);
t_token		*word_token(char *prompt, int *index);

#endif
