/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:52:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 17:33:20 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer/lexer.h"
#include "metachars.h"

//is <>, <<>>
int	is_redirection(char *line, int index)
{
	return (line[index] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0]
		|| (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]));
}

void	syntax_error(t_context *context, char *metachars)
{
	context->error_code = SYNTAX_ERROR;
}

//if |, <>, <<>>
int	check_metachar(t_context *context, char *line, int i)
{
	if (line[i] == PIPE[0])
		return (syntax_error(context, PIPE), 0);
	else if (line[i] == INPUT_RD[0] && line[i + 1] == INPUT_RD[0])
		return (syntax_error(context, HERE_DOC_RD), 0);
	else if (line[i] == OUTPUT_RD[0] && line[i + 1] == OUTPUT_RD[0])
		return (syntax_error(context, APPEND_RD), 0);
	else if (line[i] == INPUT_RD[0])
		return (syntax_error(context, INPUT_RD), 0);
	else if (line[i] == OUTPUT_RD[0])
		return (syntax_error(context, OUTPUT_RD), 0);
	return (1);
}
