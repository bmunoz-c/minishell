/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:18:25 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/10 22:22:19 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*build_cmd(t_data *data, t_token *tk)
{
		
}
void	add_cmd(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!cmd_list)
	{
		*cmd_list = cmd;
		return ;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

// Takes the tk_list and creates a cmd_list,
// Basically it's a list with all cmds in the prompt
// and it's necessary info to execute them
t_cmd	*group_cmd(t_data *data, t_token *tk_list)
{
	t_token	*tk;
	t_cmd	*cmd;
	t_cmd	*cmd_list;

	tk = tk_list;
	while (tk) // Create a cmd for each pipe
	{
		if (tk->type == PIPE)
		{
			cmd = build_cmd(data, tk);
			add_cmd(&cmd_list, cmd);
		}
		tk = tk->next;
	}
	// There is no pipes so it's only one command
	if (!cmd_list)
	{
		cmd = build_cmd(data, tk);
		add_cmd(&cmd_list, cmd);
	}
	return (cmd_list);
}
