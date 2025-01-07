/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:47:49 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/07 16:35:07 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env *new_env(char *key)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if(!env)
		return (free_ptr(env));
	env->key = key;
	env->value = ft_strdup(getenv(key));
	if (!env->value)
		env->value = ft_strdup("");
	env->next = NULL;
	return (env);
}

void add_env(t_env **env_list, t_env *new_env)
{
	t_env	*tmp;

	if (!env_list || !*env_list)
	{
		*env_list = new_env;
		new_env->prev = NULL;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
	new_env->prev = tmp;
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(key))
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
				return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}
char	**env_as_matrix(t_env *env)
{
	char **data;
	t_env *tmp;
	int i;

	i = 0;
	tmp = env;
	while (env)
	{
		i++;
		env = env->next;
	}
	data = malloc(sizeof(char *) * (i + 1));
	if (!data)
		return (NULL);
	i = 0;
	env = tmp;
	while (env)
	{
		data[i] = ft_strjoin(env->key, "=");
		data[i] = ft_strjoin_f(data[i], env->value, 1);
		i++;
		env = env->next;
	}
	data[i] = NULL;
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
		tmp_env = new_env(key);
		if(!tmp_env)
			return free_env(data->env);
		add_env(&(data->env), tmp_env);
		tmp_env = NULL;
		i++;
	}
	data->env_matrix = env_as_matrix(data->env);
}



