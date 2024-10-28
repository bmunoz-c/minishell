/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/28 18:51:48 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env_value(t_env *env, char key)
{
	(void)env;
	(void)key;
	return ("tinkywinky");
}

//Search key in str, return value found in env.
char	*value_search(t_data *data, char *str, int *index)
{
	char	*key;
	char	*value;
	int		j;
	int		len;

	j = *index;
	len = 0;
	while (str[++j] && !is_space(str[j]) && str[j] != '$')
		len++;
	key = ft_substr(str, *index, len);
	if (!key)
		return (NULL);
	value = ft_strdup(get_env_value(&data->env, key));
	free(key);
	if (!value)
		return (NULL);
	*i = j;
	return (value);
}

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
