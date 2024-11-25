/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:03 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/25 19:35:02 by borjamc          ###   ########.fr       */
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
        if ((*token)->type == WORD
            || (*token)->type == SQ_STR || (*token)->type == DQ_STR)
            tmp = merge_token(token);
        //Si merge_token devuelve un nuevo token combinado (almacenado en tmp)
        if (!tmp)
            break;
        //Si tmp->next es NULL, no hay más tokens y se actualiza *token. Termina el bucle.
        else if (!tmp->next)
        {
            *token = tmp;
            break ;
        }
        //Si tmp->next existe, avanza al siguiente token (*token = (*token)->next).
        else
        {
            *token = tmp;
            *token = (*token)->next;
            tmp = *token;
        }
    }
    //Después de recorrer la lista, retrocede al primer token utilizando (*token)->prev.
    while ((*token) && (*token)->prev)
        *token = (*token)->prev;
}

// Actualiza la lista de tokens.
// AFTER: A = &token_list / B = old_t / C = B->next (tmp) / X = new_t.
// ANTES: A <-> B <-> C || DESPUES: A <-> X <-> C

void    update_list(t_token **token, t_token *new_t, t_token *tmp, t_token *old_t)
{
    //Actualizar new_t
    new_t->prev = old_t->prev;
    new_t->next = tmp;
    //Actualizar C (tmp) para conectar con X (new_t)
    if (tmp)
    {
        tmp->prev->next = NULL;
        tmp->prev = new_t;
    }
    //Actualizar A (token) para conectar con X (new_t)
    if (old_t->prev)
        old_t->prev->next = new_t;
    else
        *token = new_t;
    //Liberar old_t
    free_token(&old_t);    
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
    //trim para marcar el inicio del rango de tokens que se combinarán.
    t_token *trim;
    char *newcontent;

    newtoken = NULL;
    trim = *token;
    tmp = *token;
    newcontent = ft_strdup("");
    while (tmp && (tmp->type == WORD || tmp->type == SQ_STR || tmp->type == DQ_STR))
    {
        //Si el contenido de tmp existe, lo agrega a newcontent usando ft_strjoin_f.
        if (tmp->content)
            newcontent = ft_strjoin_f(newcontent, tmp->content);
        tmp = tmp->next;
    }
    //Si su longitud es > 0, crea un nuevo token con el contenido combinado.
    if (ft_strlen(newcontent) > 0)
    {
        newtoken = new_token(newcontent, (*token)->type);
        update_list(token, newtoken, tmp, trim);
    }
    //Si el nuevo token tiene un siguiente nodo (newtoken->next), devuelve ese nodo.
    if (newtoken && newtoken->next)
        return (newtoken->next);
    return (newtoken);  
}
// Quitar espacios y tokens vacios.
// Check sintax errors.