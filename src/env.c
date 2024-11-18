/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:47:49 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 13:13:22 by ltrevin-         ###   ########.fr       */
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
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}
char	*get_env_value(t_env *env, char *key)
{
		if (ft_strlen(env->key) == ft_strlen(key) && ft_strncmp(env->key, key, ft_strlen(key)) == 0)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
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
}


