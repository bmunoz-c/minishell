/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:50:47 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/24 13:53:32 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void print_env(t_env *env)
{
	
	printf("---------- PRINTING ENV -----------\n");
	while(env)
	{
		printf("key: %s \t\tvalue: %s\n", env->key, env->value);
		env = env->next;
	}
	printf("--------- END PRINT ENV -----------\n");
}

void free_env(t_env *env)
{
	t_env *tmp;

	while(env)
	{
		tmp = env;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		env = env->next;
	}
}


char *get_env_value(t_env *env, char *key)
{
	while(env)
	{
		if(ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return(env->value);
		env = env->next;
	}
	return (NULL);
}
