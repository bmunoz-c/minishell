/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:47:49 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/24 13:53:35 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env *new_env(char *key)
{
	t_env *env;

	env = malloc(sizeof(t_env));
	if(!env)
		return (ft_memdel(env));
	env->key = key;
	env->value = ft_strdup(getenv(key));
	env->next = NULL;
	//if(env)
	//	printf("Created %s=%s\n", env->key, env->value);
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

void copy_env(char **org_env, t_data *data)
{
	int i;
	char *key;
	t_env *tmp_env;

	i = 0;
	while(org_env[i])
	{
		key = ft_substr(org_env[i], 0, ft_index_ch(org_env[i], '='));
		tmp_env = new_env(key);
		add_env(&(*data).env, tmp_env);
		i++;
	}
}


