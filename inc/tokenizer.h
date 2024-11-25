/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/25 19:37:20 by borjamc          ###   ########.fr       */
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

typedef struct s_cmd {
    char *path;          // Path to the executable or built-in command
    int  nargs;
    char **args;         // Array of arguments for the command, including the command name
    char *input_file;    // File for input redirection, or NULL if not used
    char *output_file;   // File for output redirection, or NULL if not used
    //int append_output;   // Flag for >> redirection)
    struct s_cmd *next;
} t_cmd;

//_____TOKEN_STRUCT_____//
typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	struct s_token		*next;
	struct s_token		*prev;

}	t_token;

typedef struct s_data
{
	t_token		*token_list;		//Puntero a una lista de tokens
	t_env		*env;
	char		**path;
	char		*prompt;
	int			err_code;
	char		*err_msg;
	t_cmd		*cmd_list;

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

//_____EXPANSOR_____//
void		expansor(t_token **token, t_data *data);
//_____expansor_utils_____//
char		*value_search(t_data *data, char *str, int *index);
char		*expand_str(t_data *data, char *str, int i);

//_____PREP_EXEC_____//
void 		quote_type(t_token **token);
void    	update_list(t_token **token, t_token *new_t, t_token *tmp, t_token *old_t);
t_token 	*merge_token(t_token **token);


#endif