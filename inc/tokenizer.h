/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:32:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/25 06:14:28 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <structs.h>

//_____TOKENIZER_____//
//_____add_new_token_____//
int		tokenizer(t_data *data, int i);
t_token	*new_token(char *_content, t_token_type _type);
void	add_token(t_token **token_list, t_token *new_token);
void	print_token(t_token *token);
void	print_token_list(t_token *token_list);
//_____token_type_____//
t_token	*sp_token(char *prompt, int *index);
t_token	*meta_token(t_data *data, char *prompt, int *index);
t_token	*quote_token(char *prompt, int *index, t_token_type type);
t_token	*word_token(char *prompt, int *index);

//_____EXPANSOR_____//
void	expansor(t_token **token, t_data *data);
//_____expansor_utils_____//
char	*value_search(t_data *data, char *str, int *index);
char	*expand_str(t_data *data, char *str, int i);

//_____PREP_EXEC_____//
void	merge_tokens(t_token **token);
t_token	*merge_token(t_token *token, t_token **merge_last_t);
//_____SYNTAX_____//
int		syntax_error_msg(t_data *data, char *ch_err);
int		syntax_error(t_data *data, t_token **token, int before_heredoc);

#endif
