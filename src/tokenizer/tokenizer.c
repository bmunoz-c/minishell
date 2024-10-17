/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 18:49:05 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	safe_token(t_token *token_list, char *prompt)
{
	int		i;
	t_token	*token;

	i = 0;
	prompt = ft_strtrimifree(prompt, " ", 1);
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			token = sp_token(prompt, &i);
		else if (is_redirection(prompt[i], &i) || prompt[i] == '|')
			token = meta_token(prompt[i], &i);
		else if (prompt[i] == '"')
			token = quote_token(prompt[i], &i, DQ_STR);
		else if (prompt[i] == '\'')
			token = quote_token(prompt[i], &i, SQ_STR);
		if (!token)
			return (1);
		else
			add_token(&(data->token_list), token);
		if (prompt[i])
			i++;
	}
	return (0);
}

//Create a new token: type & content
t_token	*new_token(char *_content, t_token_type _type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = _type;
	token->content = _content;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

//Add a new token to the list.
void	add_token(t_token **token_list, t_token *new_token)
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
