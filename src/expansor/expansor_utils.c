/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/31 17:38:23 by borjamc          ###   ########.fr       */
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
	if (!value)
		return (NULL);
	*index = j;
	return (value);
}
/*
char	*expand_str(char *str, t_data data)
{
	int		i;
	char	*content_;

	i = 0;
	content_ = NULL;
	if (str[0] == '$' && str[1] == '\0')
		return ('$');
	while (str[i] && str[i] != '$')
		i++;
}

char	*expand_dq_str(char *str, t_data data)
{
	int		i;
	char	*content_;

	i = 0;
	content_ = NULL;
	while (str[i])
	{
		while (str[i] != '\0' && str[] != '$')
			i++;
		content_ = ft_substr(str, 0, i) ;
	}
	return (content_);
}
*/