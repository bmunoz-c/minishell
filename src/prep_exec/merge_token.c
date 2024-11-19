/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:03 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/19 21:38:56 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Merge tokens of type WORD, SQ_STR, DQ_STR.
void quote_type(t_token **token)
{
    t_token *tmp;

    tmp = NULL;
    while (*token)
    {
        if ((*token)->type = WORD || (*token)->type == SQ_STR || (*token)->type == DQ_STR)
        {
            tmp = merge_token(token);
        }
        if (!tmp)
            break;
    }
}

t_token *merge_token(t_token **token)
{
    t_token *tmp;
    t_token *newtoken;
    char *newcontent;

    tmp = *token;
    newtoken = NULL;
    newcontent = ft_strdup("");
    while (tmp && (tmp->type == WORD || tmp->type == SQ_STR || tmp->type == DQ_STR))
    {
        if (tmp->content)
            newcontent = ft_strjoin_f(newcontent, tmp->content);
        tmp = tmp->next;
    }
    if (ft_strlen(newcontent) > 0)
    {
        newtoken = new_token(newcontent, (*token)->type);
        //recolocar token
    }
    if (newtoken && newtoken->next)
        return (newtoken->next);
    return (newtoken);  
}
// Quitar espacios y tokens vacios.
// Check sintax errors.