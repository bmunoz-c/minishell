/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:28:00 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/17 21:13:21 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	tokenizer(t_data *data, int i)
{
	t_token	*token;

	data->prompt = ft_strtrimfree(data->prompt, " ", 1);
	while (data->prompt[i])
	{
		if (data->prompt[i] == ' ')
			token = sp_token(data->prompt, &i);
		else if (data->prompt[i] == '<' || data->prompt[i] == '>'
			|| data->prompt[i] == '|')
			token = meta_token(data->prompt, &i);
		else if (data->prompt[i] == '"')
			token = quote_token(data->prompt, &i, DQ_STR);
		else if (data->prompt[i] == '\'')
			token = quote_token(data->prompt, &i, SQ_STR);
		else
			token = word_token(data->prompt, &i);
		if (!token)
			return (1);
		else
			add_token(&(data->token_list), token);
		if (data->prompt[i])
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

//********** HASTA AQUIIIII **********


char *get_tokentype(int n)
{
	switch (n)
	{
		case WORD: return "WORD";
		case SPC: return "SPC";
		case PIPE: return "PIPE";
		case SQ_STR: return "SQ_STR";
		case DQ_STR: return "DQ_STR";
		case ENV_VAR: return "ENV_VAR";
		case HERE_DOC: return "HERE_DOC";
		case INPUT: return "INPUT";
		case OUTPUT: return "OUTPUT";
		case APPEND: return "APPEND";
	}
	return (NULL);
}

void	print_token(t_token *token)
{
	printf("Token_Dir %p\n", token);
	printf("Type: %s\n", get_tokentype(token->type));
	printf("Content: ~%s~\n", token->content);
	//printf("Next dir: %p\n", token->next);
	//printf("Prev dir: %p\n", token->prev);
	printf("**********************************\n");
}

void	print_token_list(t_token *token_list)
{
	t_token	*tmp;
	int i;

	i = 0;
	tmp = token_list;
	while (tmp)
	{
		print_token(tmp);
		tmp = tmp->next;
		i++;
	}
	printf("Tkn count: %d\n", i);
	printf("******** END PRINT TOKEN ********\n");
}
