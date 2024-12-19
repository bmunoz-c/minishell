/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/19 17:23:52 by borjamc          ###   ########.fr       */
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

//ESTRUCTURA ENUMERACION TIPO DE TOKEN
typedef enum e_token_type
{
	SPC,
	WORD,
	SQ_STR,
	DQ_STR,
	PIPE,
	//____Redirections_____//
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC,
	ENV_VAR,
}	t_token_type;



typedef struct s_cmd
{
	char			*path;
	int				nargs;
	char			**args;
	int 			in_fd;
    int 			out_fd;
	int				append_output;
	int				builtin;
	struct s_cmd	*next;
}	t_cmd;

//_____TOKEN_STRUCT_____//
typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	struct s_token		*next;
	struct s_token		*prev;

}	t_token;

//_____ENVIRONMENT_STRUCT_____//
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	int				match;
}	t_env;



//_____DATA_______STRUCT_____//
typedef struct s_data
{
	t_token		*token_list;
	t_env		*env;
	char		**path;
	char		*prompt;
	int			err_code;
	char		*err_msg;
	t_cmd		*cmd_list;
	char **env_matrix;
}	t_data;




//_____TOKENIZER_____//
//_____add_new_token_____//
int			tokenizer(t_data *data, int i);
t_token		*new_token(char *_content, t_token_type _type);
void		add_token(t_token **token_list, t_token *new_token);
void		print_token(t_token *token);
void		print_token_list(t_token *token_list);
//_____token_type_____//
t_token		*sp_token(char *prompt, int	*index);
t_token		*meta_token(t_data *data, char *prompt, int *index);
t_token		*quote_token(char *prompt, int *index, t_token_type type);
t_token		*word_token(char *prompt, int *index);

//_____EXPANSOR_____//
void		expansor(t_token **token, t_data *data);
//_____expansor_utils_____//
char		*value_search(t_data *data, char *str, int *index);
char		*expand_str(t_data *data, char *str, int i);

//_____PREP_EXEC_____//
void		merge_tokens(t_token **token);
t_token		*merge_token(t_token *token, t_token **merge_last_t);
//_____SYNTAX_____//
int			syntax_error_msg(t_data *data, char *ch_err);
int			syntax_error(t_data *data, t_token **token);

#endif