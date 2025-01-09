/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:45:29 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/09 19:52:13 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
This function receives a string to verify if it has
a valid variable name to export. 

Ret     0 if found invalid chars
		1 if there is no operator, 
        2 if the operator is "+=" and
        3 if the operator is "=".
*/
int valid_varname(char *str)
{
    int i;

    if (!str)
        return (-1);
	i = 0;
    while (str[i] == '_' || ft_isalpha(str[i]))
        i++;
    if (str[i] == '\0')
        return (1);
    if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
        return (2);
	if(str[i] == '+' && !str[i + 1])
		return (0);
    if (str[i] == '=')
        return (3);
    return (0);
}

/* 
This function receives a string and removes the "+" from
the "+=" operator.

Ret: string to edit. 
*/
char	*rm_plus(char *str)
{
	int	i;
	char *new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '+')
		i++;
	new_str = ft_substr(str, 0, i);
	if (!new_str)
		return NULL;
	new_str = ft_strjoin_f(new_str, ft_substr(str, i + 1, ft_strlen(str) - i - 1), 3);
	/* while (str[i] && str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	} */
	//str[i] = '\0';
	return (new_str);
}

/*
- If the variable already exists and there is no operator, it returns.
- If the variable already exists and there is an operator of type 3,
    substitute the VALUE.
- If not, create the new environment variable and add it to the list.

Ret     0 if the name of the variable is not valid,
		1 if there is no operator, 
        2 if the operator is "+=" and
        3 if the operator is "=".

*/
char *export_var(t_env *env, char *arg, t_data *data)
{
	char *value;
	char *old_value;
	
	if (arg == NULL)
		return (NULL);
	value = ft_substr(arg, ft_index_ch(arg, '=') + 1, 
		ft_strlen(arg) - ft_index_ch(arg, '=') - 1);	
	if(env)
	{
		old_value = env->value;
		if(value)
			env->value = value;
		else
			env->value = ft_strdup("");
	}
	else
	{
		env = new_env(env->key, value);
		if(!env)
			return NULL;
		add_env(&data->env, env);
		old_value = NULL;
	}
	free_ptr(value);
	return (old_value);
}
