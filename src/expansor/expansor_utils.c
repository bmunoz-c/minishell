/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/08 20:59:45 by bmunoz-c         ###   ########.fr       */
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
void	expand_str(t_token *token, t_data *data, char *str)
{
	int		i;
	int		lst_size;
	char	*value;
	char	**lst_value;
	int		start;

	str = token->content;
	i = 0;
	lst_value = (char **)malloc(sizeof(char *)* ft_strlen(str)+1);
	if (str[0] == '$' && str[1] == '\0')
		return ;
	lst_size = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			value = value_search(data, str, &i);
			if (value)
				lst_value[lst_size] = ft_strdup(value);
			else
				lst_value[lst_size] = ft_strdup("");
		}
		else
		{
			start = i;
			while (str[i + 1] && str[i + 1] != '$')
				i++;
			lst_value[lst_size] = ft_substr(str, start, i - start + 1);
			if (str[i] == '$' && !str[i+1])
				break;
		}
		if (str[i] && str[i] != '$')
			i++;
		if (str[i])
			lst_size++;
	}
	//sobrescribir el value token con el resultado de concat_value.
	i = 0;
	printf("lst_size: %d\n", lst_size);
	while (i <= lst_size)
	{
		printf("[%d] %s\n",i , lst_value[i]);
		i++;
	}
}

//tener en cuenta si termina en $.