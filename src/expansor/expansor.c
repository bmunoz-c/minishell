/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:42:34 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/17 21:55:10 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*last_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

// TO DO: Cambiar la creacion del data a lafuncion
void	concat_tokens(t_token **head, t_token **token)
{
	t_token	*tmp;
	t_data	data;
	t_token	*last_t;

	printf("$$$$$$$$$$$$$$$$$$$$$$$$\n");
	data.prompt = ft_strdup((*token)->content);
	data.token_list = NULL;
	tokenizer(&data, 0);
	tmp = data.token_list;
	last_t = last_token(tmp);
	if ((*token)->next)
	{
		last_t->next = (*token)->next;
		(*token)->next->prev = last_t;
	}
	if ((*token)->prev)
	{
		(*token)->prev->next = tmp;
		tmp->prev = (*token)->prev;
	}
	else
	{
		*head = tmp;
		tmp->prev = NULL;
	}
}

void	expansor(t_token **token, t_data *data)
{
	t_token	*tmp;
	char	*newcont;

	tmp = *token;
	while (tmp)
	{
		// printf("Content: %s\n", tmp->content);
		if ((tmp->type == WORD || tmp->type == DQ_STR)
			&& ft_search_ch(tmp->content, '$'))
		{
			newcont = expand_str(data, tmp->content, 0);
			free(tmp->content);
			tmp->content = newcont;
		}
		if (tmp->type == WORD)
			concat_tokens(&data->token_list, &tmp);
		tmp = tmp->next;
	}
}
