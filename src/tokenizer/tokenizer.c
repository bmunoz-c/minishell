/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/15 19:59:27 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ""

int	safe_token(t_token *token_list, char *prompt)
{
	int	i;
	t_token *token;

	i = 0;
	//Limpiar espacios antes y despues
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			token = sp_token(prompt, index)
		else if (is_metachar(prompt[i]))
		else if (is_quote(prompt[i], type))

		if (!token)
			return (1);
		else
			add_token(&(data->token_list), token);
			
		i++;
	}
	return(0);
}

t_token	*sp_token(char *prompt, int	*index)
{
	int	i;
	char	*content;

	i = *index;
	while (prompt[i] && prompt[i] == ' ')
		i++;
	content = malloc(sizeof(char) * 2);
	if (!content)
		return (NULL);
	content[0] == ' ';
	content[1] == '\0';
	*index = i;

	return (new_token(token));
}

t_token *new_token(char *_content, t_token_type _type)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = _type;
	token->content = _content;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void add_token(t_token **token_list, t_token *new_token)
{
	t_token	*tmp;

	if (!*token_list)
	{
		*token_list = new_token;
		return ;
	}
	tmp = *token_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
	new_token->prev = tmp;
}
/*
t_token	*meta_token(char *prompt, int *index)
{
	int	i;

	i = 0;

	if (prompt[i] == '|')
	
}*/
