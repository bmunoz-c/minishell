/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:42:34 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/22 17:41:26 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expansor_type(t_data *data, t_token **token)
{
	t_token	*tmp;

	tmp = token;
	//Si es un string
	if (tmp->type == WORD)
	{
		//tmp->content = expand_str(data));
	}
	//Si es una string con comillas simples
	else if (tmp->type == SQ_STR)
	{
		//No expande
	}
	//Si es una string con comillas  dobles
	else if (tmp->type = DB_STR)
	{
		//tmp->content = (expand_dq_str(data));

	}
}

t_token	expansor(t_token **token, t_data *data)
{
	char	*content;
	t_token	*tmp;
	t_token	*new_t;
	t_token	*new_t_lst;

	tmp = *token;
	while (tmp)
	{
		content = expansor_type(data, type);
		new_t = new_token(content, type);
		if (!new_t)
			return (NULL);
		add_token(new_t_lst, new);
		tmp = tmp->next;
	}
	return (new_t_lst);
}
