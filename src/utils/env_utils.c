/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:47:49 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/13 22:29:00 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (free_ptr(env));
	env->key = key;
	env->value = ft_strdup(value);
	if (!env->value)
		env->value = ft_strdup("");
	env->next = NULL;
	return (env);
}

void	add_env(t_env **env_list, t_env *new_env)
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

t_env	*get_env(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strlen(env->key) == ft_strlen(key))
		{
			if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}

void	change_env_value(char *key, char *value, t_env **env_lst)
{
	t_env	*temp;

	temp = *env_lst;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			if (temp && temp->value)
				free(temp->value);
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
}
