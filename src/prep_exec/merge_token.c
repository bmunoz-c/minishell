/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:03 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/26 20:05:20 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Limpia espacions y tokens vacios
void	clear_list(t_token **token_list)
{
	t_token	*token;
	t_token	*tmp;

	token = *token_list;
	while (token)
	{
	if (token->type == SPC || ft_strlen(token->content) == 0)
	{
		if (token->prev)
		{
			token->prev->next = token->next;
		}
		if (token->next)
		{
			token->next->prev = token->prev;
		}
		tmp = token;
		free_token(tmp);
		
	}
	
	//checkear TODO
	token = token->next;
}

void	update_list(t_token **token_list, t_token **tmp,
		t_token **merge_last_t, t_token **token)
{
	if ((*token)->prev)
	{
		(*token)->prev->next = *tmp;
		(*tmp)->prev = (*token)->prev;
	}
	else
		*token_list = *tmp;
	if ((*merge_last_t)->next)
	{
		(*merge_last_t)->next->prev = *tmp;
		(*tmp)->next = (*merge_last_t)->next;
	}
	(*merge_last_t)->next = NULL;
	free_tokens(*token);
	*token = *tmp;
}

// Merge tokens of type WORD, SQ_STR, DQ_STR.
void	merge_tokens(t_token **token_list)
{
	t_token	*tmp;
	t_token	*token;
	t_token	*merge_last_t;

	tmp = NULL;
	token = *token_list;
	merge_last_t = NULL;
	while (token)
	{
		if (token->type == WORD || token->type == SQ_STR
			|| token->type == DQ_STR)
		{
			tmp = merge_token(token, &merge_last_t);
			if (tmp)
				update_list(token_list, &tmp, &merge_last_t, &token);
		}
		token = token->next;
	}
	clear_list(token_list);
}

t_token	*merge_token(t_token *token, t_token **merge_last_t)
{
	t_token	*tmp;
	t_token	*newtoken;

	(void)merge_last_t;
	newtoken = new_token(ft_strdup(token->content), SQ_STR);
	tmp = token->next;
	while (tmp && (tmp->type == WORD || tmp->type == SQ_STR
			|| tmp->type == DQ_STR))
	{
		newtoken->content = ft_strjoin_f(newtoken->content, tmp->content, 1);
		*merge_last_t = tmp;
		tmp = tmp->next;
	}
	if (ft_strlen(newtoken->content) <= ft_strlen(token->content))
	{
		free_token(newtoken);
		newtoken = NULL;
	}
	return (newtoken);
}
// Quitar espacios y tokens vacios.
// Check sintax errors.