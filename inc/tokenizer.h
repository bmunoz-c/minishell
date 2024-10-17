/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 18:12:14 by bmunoz-c         ###   ########.fr       */
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
	enum e_token_type	type;
	char				*content;
	struct s_token		*next;
	struct s_token		*prev;

}	t_token;

typedef struct s_data
{
	t_token		*token_list;
	char		**env;
	char		**path;
	char		*prompt;
	int			err_code;
	char		*err_msg;

}	t_data;

//_____SYNTAX_____//
int			check_quotes(t_data *data);
int			check_pipe(t_data *data, char *line, int index);
int			check_redirection(t_data *data, char *line, int index);
int			check_syntax(t_data *data);

//_____SYNTAX_UTILS_____//
int			is_redirection(char *line, int index);
void		metachars_error(t_data *data, char *metachars);
int			check_metachar(t_data *data, char *line, int i);

//_____ERRORS_____//
void		metachars_error(t_data *data, char *metachars);
int			syntax_error(t_data *data, char *msg);


//_____TOKENIZER_____//
//_____new_token_____//
int			safe_token(t_token *token_list, char *prompt);
t_token		*new_token(char *_content, t_token_type _type);
void		add_token(t_token **token_list, t_token *new_token);
//_____token_type_____//
t_token		*sp_token(char *prompt, int	*index);
t_token		*meta_token(char *prompt, int *index);
t_token		*quote_token(char *prompt, int *index, t_token type);

#endif
