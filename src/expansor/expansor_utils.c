/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/19 12:08:16 by ltrevin-         ###   ########.fr       */
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
	value = ft_strdup(get_env_value(data->env, key));
	free(key);
	*index = j;
	if (!value)
		return (NULL);
	return (value);
}

void	expand_var(int *i, char **newcont, char *str)
{
	int		start;
	char	*var;

	start = *i;
	while (str[*i + 1] && str[*i + 1] != '$')
		*i += 1;
	var = ft_substr(str, start, *i - start + 1);
	*newcont = ft_strjoin_f(*newcont, var, *newcont, var);
}

char	*expand_str(t_data *data, char *str, int i)
{
	char	*value;
	char	*newcont;

	newcont = ft_strdup("");
	if (!newcont)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			value = value_search(data, str, &i);
			if (value)
				newcont = ft_strjoin_f(newcont, value, newcont, value);
		}
		else
		{
			expand_var(&i, &newcont, str);
			if (str[i] == '$' && !str[i + 1])
				break ;
		}
		if (str[i] && str[i] != '$')
			i++;
	}
	return (newcont);
}
