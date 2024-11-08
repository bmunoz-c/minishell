/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/08 21:41:28 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//Search key in str, return value found in env.
char	*value_search(t_data *data, char *str, int *index)
{
	//modificar *index, quitarlo.
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

//Esta funcion concatena los values despues de expandir.
//Se guardara en el content del token 
/*char	*concat_values(char **lst, int size)
{
	int		i;
	char	*res;

	i = 0;
	if (!res)
	    return (NULL);
	while (i < size)
	{
		res = ft_strjoin(res, lst[i]);
		i++;
	}
	return (res);
}*/

// TODO: Cambiar lst_value a char*
void	expand_str(t_data *data, char *str, int i)
{
	char	*value;
	char	*lst_value;
	int		start;

	lst_value = "";
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			value = value_search(data, str, &i);
			if (value)
				lst_value = ft_strjoin(lst_value, value);
		}
		else
		{
			start = i;
			while (str[i + 1] && str[i + 1] != '$')
				i++;
			lst_value = ft_strjoin(lst_value, ft_substr(str, start, i - start + 1));
			if (str[i] == '$' && !str[i+1])
				break;
		}
		if (str[i] && str[i] != '$')
			i++;
	}
	printf("expandeeeed!!: %s\n", lst_value);
}

//tener en cuenta si termina en $.