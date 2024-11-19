/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:03 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/20 00:26:39 by borjamc          ###   ########.fr       */
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
        //If tmp = SPC, break.
        if (!tmp)
            break;
        //If tmp is not exist, and the next one is SPC, break.
        else if (!tmp->next)
        {
            *token = tmp;
            break;
        }
        // If tmp ve another token
        else
        {
            *token = tmp;
            *token = (*token)->next;
            tmp = *token;
        }
    }
    // Go to the beginning of the list.
    while ((*token) && (*token)->prev)
        *token = (*token)->prev;
}

// Update the list of tokens.
// AFTER: A = token - B = old_t - C = tmp - X = new_t.
// ANTES: A <-> B <-> C || DESPUES: A <-> X <-> C
void    update_list(t_token **token, t_token *new_t, t_token *old_t, t_token *tmp)
{
    new_t->prev = old_t->prev;
    new_t->next = tmp;
    if (old_t->prev)
        old_t->prev->next = new_t;
    if (tmp)
    {
        tmp->prev->next = NULL;
        tmp->next->prev = new_t;
    }
    else
        *token = new_t;
    free_token(old_t);    
}

/*
void update_list(t_token **token, t_token *new_t, t_token *old_t)
{
    if (!old_t || !new_t)
        return;

    new_t->prev = old_t->prev;
    new_t->next = old_t->next;

    if (old_t->prev)
        old_t->prev->next = new_t;
    else
        *token = new_t;

    if (old_t->next)
        old_t->next->prev = new_t;

    free_token(old_t);
}
*/

t_token *merge_token(t_token **token)
{
    t_token *tmp;
    t_token *newtoken;
    t_token *trim;
    char *newcontent;

    tmp = *token;
    newtoken = NULL;
    trim = *token;
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
        update_list(token, newtoken, tmp, trim);
    }
    if (newtoken && newtoken->next)
        return (newtoken->next);
    return (newtoken);  
}
// Quitar espacios y tokens vacios.
// Check sintax errors.