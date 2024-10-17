/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:07:39 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 18:19:25 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Token: ' '
t_token	*sp_token(char *prompt, int	*index)
{
	int		i;
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
	return (new_token(token. SPC));
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
	return (NULL);
}

//Token: '' ""
t_token	*quote_token(char *prompt, int *index, t_token type)
{
	int		i;
	char	*content;

	i = *index;
	i++;
	if (!prompt[i])
		return (new_token(strdup(""), type));
	while (prompt[i] && prompt[i] != prompt[index])
		i++;
	*index = i;
	if (prompt[i] == '\'')
	{
		content = ft_substr(prompt, *index, (i - *index));
		if (!content)
			return (NULL);
		return (new_token(NULL, SQ_STR));
	}
	else if (prompt[i] == '"')
	{
		content = ft_substr(prompt, *index, (i - *index));
		if (!content)
			return (NULL);
		return (new_token(NULL, DQ_STR));
	}
	return (NULL);
}
