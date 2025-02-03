/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:07:39 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/02/03 13:51:46 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Token: ' '
// Be careful multiple spaces
//

t_token	*sp_token(char *prompt, int *index)
{
	int		i;
	char	*content;

	i = *index;
	if (ft_is_space(prompt[i + 1]))
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		i -= 1;
	}
	content = malloc(sizeof(char) * 2);
	if (!content)
		return (NULL);
	content[0] = ' ';
	content[1] = '\0';
	*index = i;
	return (new_token(content, SPC));
}

// Tokens: | > < >> <<
t_token	*meta_token(t_data *data, char *prompt, int *index)
{
	int	i;

	i = *index;
	if (prompt[i] == '|')
	{
		if (prompt[i + 1] != '|')
			return (new_token(ft_strdup(""), PIPE));
		syntax_error_msg(data, "||");
	}
	else if (prompt[i] == '>' && prompt[i + 1] == '>')
	{
		*index += 1;
		return (new_token(ft_strdup(""), APPEND));
	}
	else if (prompt[i] == '<' && prompt[i + 1] == '<')
	{
		*index += 1;
		return (new_token(ft_strdup(""), HERE_DOC));
	}
	else if (prompt[i] == '>')
		return (new_token(ft_strdup(""), OUTPUT));
	else if (prompt[i] == '<')
		return (new_token(ft_strdup(""), INPUT));
	return (NULL);
}

// Token: '' ""
t_token	*quote_token(char *prompt, int *index, t_token_type type)
{
	int		i;
	char	*content;

	i = *index + 1;
	if (!prompt[i])
		return (new_token(ft_strdup(""), type));
	while (prompt[i] && prompt[i] != prompt[*index])
		i++;
	content = ft_substr(prompt, *index + 1, i - *index - 1);
	if (!content)
		return (NULL);
	*index = i;
	return (new_token(content, type));
}

t_token	*word_token(char *prompt, int *index)
{
	int		i;
	char	*content;

	i = *index;
	if (!ft_is_metachar(prompt[i + 1]) && !ft_is_space(prompt[i + 1]))
	{
		while (prompt[i] && !ft_is_metachar(prompt[i])
			&& !ft_is_space(prompt[i]))
			i++;
		i -= 1;
	}
	content = ft_substr(prompt, *index, i - *index + 1);
	if (!content)
		return (NULL);
	*index = i;
	return (new_token(content, WORD));
}
