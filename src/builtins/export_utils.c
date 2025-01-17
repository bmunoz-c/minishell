/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 18:05:01 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/17 18:33:10 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_key(char *str)
{
	char	*key;

	if (!ft_search_ch(str, '='))
		key = ft_strdup(str);
	else
		key = ft_substr(str, 0, ft_index_ch(str, '='));
	if (ft_search_ch(key, '+'))
		key = rm_plus(key);
	return (key);
}

void	update_environment(t_data *data, const char *arg, char *key,
		int export_code)
{
	char	*old;
	t_env	*env;

	env = get_env(data->env, key);
	old = export_var(env, rm_plus(ft_strdup(arg)), data, key);
	if (export_code == 1)
		print_env(data->env);
	if (old && export_code == 2)
		env->value = ft_strjoin_f(old, env->value, 2);
	free_ptr(old);
	data->env_matrix = env_as_matrix(data->env, data->env_matrix);
}
