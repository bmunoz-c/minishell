/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/15 21:43:47 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	safe_token(t_token *token_list, char *prompt)
{
	int	i;
	t_token *token;

	i = 0;
	//Limpiar espacios antes y despues con strtrim
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
	return(0);
}

//Token: ' '
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

//Create a new token: type & content
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

//Add a new token to the list.
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

//Tokens: | > < >> <<
t_token	*meta_token(char *prompt, int *index)
{
	int		i;

	i = *index;
	if (prompt[i] == '|')
		return (new_token(NULL, PIPE));
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		*index += 1;
		return (new_token(NULL, APPEND));
	}
	else if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		*index += 1;
		return (new_token(NULL, HERE_DOC));
	}
	else if (prompt[i] == '>')
		return (new_token(NULL, OUTPUT));
	else if (prompt[i] == '<')
		return (new_token(NULL, INPUT));
	return (new_token(token));
}

//Token: '' ""
t_token	*quote_token(char *prompt, int *index, t_token type)
{
	int		i;

	i = *index;
	i++;
	if (!prompt[i])
		return (new_token(strdup(""), type))
	while (prompt[i] && prompt[i] != prompt[index])
	{
		
		i++;
	}
	if (prompt[i] == '\'' || '"')
	{
		ft_substr(prompt, *index, (i - *index));
		return (new_token(NULL, SQ_STR));
	}
	else if (prompt[i] == '"')
	{
		ft_substr(prompt, *index, (i - *index));
		return (new_token(NULL, DQ_STR));
	}
	return (new_token(token));
}


//ft_substr(char *line, int start, size_t len)
//len = i - *index
//start = *index
//line = prompt
