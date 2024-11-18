/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:20:51 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 19:54:54 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_data(t_data *data, int env_flag)
{
	if (!data)
		return ;
	if (data->prompt)
	{
		free_ptr(data->prompt);
		data->prompt = NULL;
	}
	if (data->env && env_flag)
	{
		free_env(data->env);
		data->env = NULL;
	}
	if (data->token_list)
	{
		free_tokens(data->token_list);
		data->token_list = NULL;
	}
	if (data->cmd_list)
	{
		free_cmds(data->cmd_list);
		data->cmd_list = NULL;
	}
}

void	free_cmds(t_cmd *cmd_list)
{
    t_cmd *tmp_lst;
    t_cmd *tmp_cmd;

    tmp_lst = cmd_list;
    while (tmp_lst)
    {
        tmp_cmd = tmp_lst;
        tmp_lst = tmp_lst->next;
        free_cmd(tmp_cmd);
        tmp_cmd = NULL;
    }
}

void	*free_cmd(t_cmd *cmd)
{
	int i;
	if (!cmd)
		return (NULL);
	if (cmd->path)
		free(cmd->path);
	if (cmd->args)
	{
		i = 0;
		while(cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	free(cmd);
	return (NULL);
}

void	free_env(t_env *env)
{
    t_env	*tmp;

    while (env)
    {
        tmp = env;
        env = env->next;
        if (tmp->key)
        {
            free(tmp->key);
            tmp->key = NULL;
        }
        if (tmp->value)
        {
            free(tmp->value);
            tmp->value = NULL;
        }
        free(tmp);
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
	printf("%s\n, TOKEN TOKEN TOKEN\n", token->content);
	if (token->content)
		free(token->content);
	token->content = NULL;
	free(token);
	token = NULL;
}