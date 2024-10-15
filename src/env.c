/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:47:49 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/15 21:36:31 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*
t_env *new_env(char *key)
{
	t_env *env;

	env = malloc(SizeOf(t_env));
	if(!env)
		return (ft_memdel(env));
	env->key = key;
	env->value = ft_strdup(getenv(key));
	//TODO: proteger si no esa en el env
}*/

void add_env(t_env **env_list, t_env *new_env)
{
	t_env	*tmp;

	if (!*env_list)
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

	i = 0;
	while(org_env[i++])
	{
		// TODO: Aqui hay que crear los nodos de env 
		// y copiarlos en la lista que guardaremos en data
		(void) data;	
	}
}
