/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/17 19:21:00 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Search key in str, return value found in env.
char	*value_search(t_data *data, char *str, int *index)
{
	char	*key;
	char	*value;
	int		j;
	int		len;

	j = *index;
	len = 0;
	while (str[++j] && !ft_is_space(str[j]) && str[j] != '$')
		len++;
	key = ft_substr(str, *index + 1, len);
	if (!key)
		return (NULL);
	printf ("KEY: %s\n", key);
	value = ft_strdup(get_env_value(data->env, key));
	free(key);
	*index = j;
	if (!value)
		return (NULL);
	return (value);
}

// TODO: Cambiar newcont a char*
void	expand_str(t_data *data, char *str, int i)
{
	char	*value;
	char	*newcont;
	int		start;

	newcont = "";
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			value = value_search(data, str, &i);
			if (value)
				newcont = ft_strjoin(newcont, value);
		}
		else
		{
			start = i;
			while (str[i + 1] && str[i + 1] != '$')
				i++;
			newcont = ft_strjoin(newcont, ft_substr(str, start, i - start + 1));
			if (str[i] == '$' && !str[i + 1])
				break ;
		}
		if (str[i] && str[i] != '$')
			i++;
	}
	printf("expandeeeed!!: %s\n", newcont);
}

//TO DO: retoquenizar si es word.
//TO DO: insertar la lista nueva en la lista de tokens.
	t_token	new_tokens;

	new_tokens = tokenizer(data, 0);
	add_token(&data->token_list, new_tokens);
	free(newcont);