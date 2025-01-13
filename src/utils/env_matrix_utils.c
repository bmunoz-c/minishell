/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_matrix_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 22:03:10 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/13 22:03:40 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**env_as_matrix(t_env *env, char **arr)
{
	char **data;
	t_env *tmp;
	int i;

	i = 0;
	tmp = env;
	while (env)
	{
		env = env->next;
		i++;
	}
	data = malloc(sizeof(char *) * (i + 1));
	if (!data)
		return (NULL);
	i = 0;
	env = tmp;
	while (env)
	{
		data[i] = ft_strjoin_f(ft_strjoin(env->key, "="), env->value, 1);
		env = env->next;
		i++;
	}
	data[i] = NULL;
	ft_free_split(arr);
	return (data);
}

void copy_env(char **org_env, t_data *data)
{
	int i;
	char *key;
	t_env *tmp_env;

	i = 0;
	while(org_env[i])
	{
		key = ft_substr(org_env[i], 0, ft_index_ch(org_env[i], '='));
		if(!key)
			return free_env(data->env);
		tmp_env = new_env(key, getenv(key));
		if(!tmp_env)
			return free_env(data->env);
		add_env(&(data->env), tmp_env);
		tmp_env = NULL;
		i++;
	}
	data->env_matrix = env_as_matrix(data->env, data->env_matrix);
}