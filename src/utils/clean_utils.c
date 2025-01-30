/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:20:51 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/17 17:59:28 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
		{
			free_ptr(tmp->key);
			tmp->key = NULL;
		}
		if (tmp->value)
		{
			free_ptr(tmp->value);
			tmp->value = NULL;
		}
		free_ptr(tmp);
		tmp = NULL;
	}
}

void	free_tokens(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list;
		token_list = token_list->next;
		free_token(tmp);
	}
}

void	free_token(t_token *token)
{
	if (token->content)
		free_ptr(token->content);
	token->content = NULL;
	if (token)
		free_ptr(token);
	token = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split || !*split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
