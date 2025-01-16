/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:04:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/13 22:26:12 by bmunoz-c         ###   ########.fr       */
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
int	valid_varname(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] == '_' || ft_isalpha(str[i]))
		i++;
	if (str[i] == '\0')
		return (4);
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
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '+')
		i++;
	if (str[i] == '\0')
		new_str = ft_strdup(str);
	else
	{
		new_str = ft_substr(str, 0, i);
		if (!new_str)
			return (NULL);
		new_str = ft_strjoin_f(new_str, ft_substr(str, i + 1, ft_strlen(str) - i
					- 1), 3);
	}
	free_ptr(str);
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
char	*export_var(t_env *env, char *arg, t_data *data, char *key)
{
	char	*value;
	char	*old_value;

	value = ft_substr(arg, ft_index_ch(arg, '=') + 1, ft_strlen(arg)
			- ft_index_ch(arg, '=') - 1);
	if (env)
	{
		old_value = ft_strdup(env->value);
		free_ptr(env->value);
		if (value)
			env->value = ft_strdup(value);
		else
			env->value = ft_strdup("");
	}
	else
	{
		env = new_env(ft_strdup(key), value);
		if (!env)
			return (NULL);
		add_env(&data->env, env);
		old_value = NULL;
	}
	free_ptr(value);
	free_ptr(arg);
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

	TODO: Anadir variable para guardar el error code y retornarlo al final
*/
int	run_export(t_data *data, t_cmd *cmd)
{
	char	*key;
	char	*old;
	t_env	*env;
	int		export_code;
	int		i;

	data->err_code = EXIT_SUCCESS;
	if (search_flags(cmd->args, "export"))
		return (SYNTAX_ERROR);
	i = 0;
	if (!cmd->args[1])
	{
		print_env(data->env);
		return (EXIT_SUCCESS);
	}
	while (cmd->args[++i])
	{
		if (!ft_search_ch(cmd->args[i], '='))
			key = ft_strdup(cmd->args[i]);
		else
			key = ft_substr(cmd->args[i], 0, ft_index_ch(cmd->args[i], '='));
		if (ft_search_ch(key, '+'))
			key = rm_plus(key);
		env = get_env(data->env, key);
		export_code = valid_varname(cmd->args[i]);
		if (export_code == 0)
		{
			printf("%s export: %s : not a valid identifier\n", PROGRAM_NAME,
				key);
			data->err_code = EXIT_FAILURE;
		}
		else
		{
			old = export_var(env, rm_plus(ft_strdup(cmd->args[i])), data, key);
			if (export_code == 1)
				print_env(data->env);
			if (old && export_code == 2)
				env->value = ft_strjoin_f(old, env->value, 2);
			free_ptr(old);
		}
		free_ptr(key);
		data->env_matrix = env_as_matrix(data->env, data->env_matrix);
	}
	return (EXIT_SUCCESS);
}
