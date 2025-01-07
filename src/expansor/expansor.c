/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:42:34 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/27 17:12:35 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//TODO Sevillana: despues del expansor, 
//joinear los tokens SQ DQ WORD si no hay otro tipo de token entre ellos +
//liberacion de espacios
t_token	*last_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

// TODO: Cambiar la creacion del data a la funcion
void	concat_tokens(t_token **head, t_token **token)
{
	t_token	*tmp;
	t_data	data;
	t_token	*last_t;

	data.prompt = (*token)->content;
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
	t_token	*old_tmp;

	tmp = *token;
	while (tmp)
	{
		if ((tmp->type == WORD || tmp->type == DQ_STR)
			&& ft_search_ch(tmp->content, '$'))
		{
			newcont = expand_str(data, tmp->content, 0);
			free(tmp->content);
			tmp->content = newcont;
			if (tmp->type == WORD && ft_strncmp(tmp->content, "", 1) && tmp->next)
			{
				old_tmp = tmp;
				concat_tokens(&data->token_list, &tmp);
				tmp = tmp->next;
				free_token(old_tmp);
				continue ;
			}
		}
		tmp = tmp->next;
	}
}
