/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:42:34 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/08 21:33:22 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*char	*expansor_type(t_data *data, t_token **token)
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
	else if (tmp->type = DQ_STR)
	{
		//tmp->content = (expand_dq_str(data));

	}
}
*/


void	expansor(t_token **token, t_data *data)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		printf("Content: %s\n", tmp->content);
		if (tmp->type == WORD)
		{
			expand_str(data, tmp->content);
			// despues de expandir hay que retokenizar e insertar en la lista de tokens
		}
		else if (tmp->type == DQ_STR)
		{
			//expansion de DQ_STR.
		}
		tmp = tmp->next;
	}
}
