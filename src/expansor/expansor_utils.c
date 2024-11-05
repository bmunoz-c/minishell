/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:22:37 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/05 20:01:47 by borjamc          ###   ########.fr       */
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
	if (!value)
		return (NULL);
	*index = j;
	return (value);
}

void	add_value(char  **lst, char *value, int *index)
{
	int		i;
	char	**new_lst;

	i = 0;
	new_lst = malloc(sizeof(char *) * (*index + 1));
	if (!new_lst)
	    return ;
	while (i < *index)
	{
		new_lst[i] = lst[i];
		i++;
	}
	new_lst[*index] = value;
	free(lst);
	lst = new_lst;
	(*index)++;
	//Guardar las expansiones y no expansiones de los values para concatenarlos

}

//Esta funcion concatena los values despues de expandir.
//Se guardara en el content del token 
char	*concat_values(char **lst, int size)
{
	int		i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	if (!res)
	    return (NULL);
	while (i < size)
	{
		res = ft_strjoin(res, lst[i]);
		i++;
	}
	return (res);
}

/*
void	expand_str(t_token *token, t_data *data)
{
	int		i;
	int		lst_size;
	char	*str;
	char	*value;
	char	**lst_value;

	str = token->content;
	i = 0;
	if (str[0] == '$' && str[1] == '\0')
		return ;
	lst_size = 0;
	while (str[i])
	{
		//solo entra si no termina en $.
		if (str[i] == '$' && str[i + 1] != '$')
		{
			value = value_search(data, str, &i);
			//guardar el value con add_value
			if (value)
				add_value(lst_value, value, &lst_size);
			else
				add_value(lst_value, ft_strdup(""), &lst_size);
		}
		else
		{
			int start;
			start = i;
			while (str[i] && str[i] != '$')
				i++;
			add_value(lst_value, ft_substr(str, start, i - start), &lst_size);
			//guardar lo demas en add_value.
		}
		i++;
	}
	//sobrescribir el value token con el resultado de concat_value.
	char *expanded_str;
	expanded_str = concat_values(lst_value, lst_size);
	token->content = expanded_str;
}
*/
//tener en cuenta si termina en $.