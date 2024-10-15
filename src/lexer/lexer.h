/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:48:18 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/11 21:54:03 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../tokenizer/tokenizer.h"

//_____LEXER_____//
int		check_pipe(t_data *data, char *line, int index);
//int		check_syntax(t_context *context, char *line);

//____LEXER_UTILS____//
int		is_redirection(char *line, int index);
void	syntax_error(t_data *data, char *metachars);
int		check_metachar(t_data *data, char *line, int i);

#endif
