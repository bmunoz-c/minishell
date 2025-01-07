/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:04:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/07 20:48:09 by ltrevin-         ###   ########.fr       */
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
		return (1);
	if (str[0] == '_' || ft_isalnum(str[0]))
	{
		i = 1;
		while (str[i] == '_' || ft_isalnum(str[i]))
			i++;
	}
	else
		return (0);
	if (str[i] == '\0')
		return (1);
	if (str[i] == '+' && str[i + 1] && str[i + 1] == '=')
		return (2);
	if (str[i] == '+' && !str[i + 1])
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
		return NULL;
	while (str[i] && str[i] != '+')
		i++;
	new_str = ft_substr(str, 0, i);
	if (!new_str)
		return NULL;
	new_str = ft_strjoin_f(new_str, ft_substr(str, i + 1, ft_strlen(str) - i - 1), 3);
	//free_ptr(str);
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
char *export_var(t_env *env, char *arg, t_data *data, char *key)
{
	char *value;
	char *old_value;
	
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
		env = new_env(key, value);
		if(!env)
			return NULL;
		add_env(&data->env, env);
		old_value = NULL;
	}
	free_ptr(value);
	return (old_value);
}


/* 
- add variable de entorno.
- si ya existe, sobreescribe.
- si no hay argumentos, imprime todas las variables de entorno.
- si hay argumentos, imprime las variables de entorno que coincidan.
 */

/* It checks whether the built-in has any operators in its arguments,
	and if so, prepares to concatenate or substitute the value. 
	If not, an error message is printed. 

	Return: int - Returns the value of the exit_status, which will depend on
	each case. In case of success, the value is 0.
*/
void   run_export(t_data *data, t_cmd *cmd)
{
	char *key;
	char *old;
	t_env *env;
	int  i;

	data->err_code = EXIT_SUCCESS;
	if(search_flags(cmd->args, "export"))
		return ;
	i = 0;
	while (cmd->args[++i])
	{
		key = ft_substr(cmd->args[i], 0, ft_index_ch(cmd->args[i], '='));
		printf("key: |%s|\n", key);
		env = get_env(data->env, key);
		if(valid_varname(cmd->args[i]) == 0)
		{
			printf("%s export: %s : not a valid identifier\n", PROGRAM_NAME, key);
			data->err_code = EXIT_FAILURE;
		}
		else
		{
			old = export_var(env, rm_plus(cmd->args[i]), data, key);
			if(old && valid_varname(cmd->args[i]) == 2)
				env->value = ft_strjoin_f(old, env->value, 3);
		}
	}
}
