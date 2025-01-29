/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:04:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/29 19:08:04 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*update_var(t_env *env, char *value)
{
	char	*old_value;

	old_value = ft_strdup(env->value);
	free_ptr(env->value);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("");
	return (old_value);
}

char	*export_var(t_env *env, char *arg, t_data *data, char *key)
{
	char	*value;
	char	*old_value;

	if (!ft_index_ch(arg, '='))
		value = NULL;
	else
		value = ft_substr(arg, ft_index_ch(arg, '=') + 1, ft_strlen(arg)
				- ft_index_ch(arg, '=') - 1);
	if (env)
		old_value = update_var(env, value);
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

int	exec_export(t_cmd *cmd, t_data *data, int i)
{
	char	*key;
	int		export_code;

	key = get_key(cmd->args[i]);
	if (!key)
	{
		ft_error("export", "not a valid identifier", 1);
		return (EXIT_FAILURE);
	}
	export_code = valid_varname(cmd->args[i]);
	if (export_code == 0)
		ft_error("export", "not a valid identifier", 1);
	else
		update_environment(data, cmd->args[i], key, export_code);
	free_ptr(key);
	return (EXIT_SUCCESS);
}

int	run_export(t_data *data, t_cmd *cmd)
{
	int		i;

	data->err_code = EXIT_SUCCESS;
	if (search_flags(cmd->args, "export"))
		return (EXIT_FAILURE);
	if (!cmd->args[1])
	{
		print_export(data->env);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (cmd->args[++i])
	{
		if (exec_export(cmd, data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
