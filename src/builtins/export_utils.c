/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:45:29 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/18 14:20:51 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
This function receives a string to verify if it has
a valid variable name to export. 

Ret     0 if the name of the variable is not valid,
		1 if there is no operator, 
        2 if the operator is "+=" and
        3 if the operator is "=".
*/
int valid_varname(char *str)
{
    int i;

    if (!str)
        return (0);
    if (str[0] == '_' || ft_isalpha(str[0]))
    {
        i = 1;
        while (str[i] == '_' || ft_isalnum(str[i]) || is_alpha(str[i]))
            i++;
    }
    else
        return (0);
    if (str[i] == '\0')
        return (1);
    if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
        return (2);
    if (str[i] == '=')
        return (3);
    return (0);        
}

/* 
This function receives a string and removes the "+" from
the "+=" operator.

Ret: string to edit. 
*/
void	remove_plus(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] && str[i] != '+')
		i++;
	while (str[i] && str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = '\0';
}

/*
- If the variable already exists and there is no operator, it returns.
- If the variable already exists and there is an operator of type 3,
    substitute the VALUE.
- If not, create the new environment variable and add it to the list.
*/
void	export_var(char *new_var, t_env *env)
{
	char	*updated_var;
    int     oper_type;

	updated_var = NULL;
	if (ft_strlen(env->key) >= 0 && oper_type == 1)
		return ;
	else if (ft_strlen(env->key) >= 0 && oper_type == 3)
	{
		updated_var = ft_strdup(new_var);
        if (!updated_var)
            return ;
		free (env->key);
		env->key = NULL;
		env->key = updated_var;
	}
	/* else
	{
		data->env = add_to_array(&data->env, new_var);
		free_ptr(updated_var);
    } */
}

void	prepare_join(t_data *data, char *join_var, int var_in_env)
{
	if (var_in_env >= 0)
		join_values(data, join_var, var_in_env);
	else
	{
		data->env = add_to_array(&data->env, join_var);
		malloc_protection(data->env, data);
	}
}

/* 
This function checks if with the built-in unset is passed 
an option.

Ret: 1 if it is a flag, 0 if it is not.
*/
int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[i] != '-')
		return (0);
	if (str[i] == '-' && (str[i] + 1) == '\0')
		return (0);
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}
