/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:05:01 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/31 07:37:52 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	valid_varname(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	if (ft_isdigit(str[i]))
		return (0);
	while (str[i] == '_' || ft_isalnum(str[i]))
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
	Print the environment variables in the format
	"declare -x key=value".
*/
void	print_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
}

/*
	Get the key from a string before the first '='.
*/
char	*get_key(char *str)
{
	char	*key;

	if (str[0] == '\0')
		return (NULL);
	if (!ft_search_ch(str, '='))
		key = ft_strdup(str);
	else
		key = ft_substr(str, 0, ft_index_ch(str, '='));
	if (ft_search_ch(key, '+'))
		key = rm_plus(key);
	return (key);
}

/*
	Update the environment variable with the new value.
*/
void	update_environment(t_data *data, const char *arg, char *key,
		int export_code)
{
	char	*old;
	t_env	*env;

	env = get_env(data->env, key);
	old = export_var(env, rm_plus(ft_strdup(arg)), data, key);
	if (export_code == 1)
		print_export(data->env);
	if (old && export_code == 2)
		env->value = ft_strjoin_f(old, env->value, 2);
	free_ptr(old);
	data->env_matrix = env_as_matrix(data->env, data->env_matrix);
}
