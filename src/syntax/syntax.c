/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:47:22 by borjamc           #+#    #+#             */
/*   Updated: 2024/11/29 02:10:10 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Check redirections and pipes
int	check_redirections(t_data *data)
{
    t_token	*token;

    token = data->token_list;
    while (token)
    {
        if (token->type == REDIR || token->type == APPEND)
        {
            if (!token->next || token->next->type != WORD)
                return (syntax_error(data, REDIR_FORMAT_ERROR));
        }
        if (token->type == PIPE)
        {
            if (!token->next || token->next->type != WORD)
                return (syntax_error(data, PIPE_FORMAT_ERROR));
        }
        token = token->next;
    }
    return (0);
}


//check HEREDOC APPEND and REDIR
//check PIPE
//check avoid quotes
//check metachars



//check syntax
int	check_syntax(t_data *data)
{
    if (check_quotes(data))
        return (syntax_error(data, QUOTE_FORMAT_ERROR));
    if (check_redirections(data))
        return (syntax_error(data, REDIR_FORMAT_ERROR));
    return (0);
}
