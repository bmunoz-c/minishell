/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:18:25 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/12 21:18:27 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// Fills the command arguments array
int	populate_args(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	int	i_args;

	i_args = 0;
	if (!cmd->args)
		return 0;
	if(cmd->args && cmd->args[0]) 
	{
		i_args = 1;
		tk_list = tk_list->next;
	}
	while (tk_list != tk_last)
	{
		if (tk_list->type == WORD || tk_list->type == SQ_STR || tk_list->type == DQ_STR)
		{
			cmd->args[i_args] = ft_strdup(tk_list->content);
			if (!cmd->args[i_args])
			{
				free_cmd(cmd);
				return (0);
			}
			i_args++;
		}
		else
			break;
		tk_list = tk_list->next;
	}
	cmd->args[i_args] = NULL; // Null-terminate the array
	return (1);
}

// Handles input and output redirections
// Function to handle input and output redirections
int search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	while (tk_list != tk_last)
	{
		if (tk_list->type == INPUT)
		{
			cmd->in_fd = open(tk_list->next->content, O_RDONLY);
			if (cmd->in_fd < 0)
				return (1);
			tk_list = tk_list->next;
		}
		else if (tk_list->type == OUTPUT || tk_list->type == APPEND)
		{
			if (tk_list->type == OUTPUT)
				cmd->out_fd = open(tk_list->next->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				cmd->out_fd = open(tk_list->next->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (cmd->out_fd < 0)
				return (1);
			tk_list = tk_list->next;
		}
		tk_list = tk_list->next;
	}
	printf("redirs handled\n");
	return (0);
}

// Main function to build the command structure
t_cmd	*build_cmd(t_data *data, t_token *tk_list, t_token *tk_last)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_data(cmd, tk_list, tk_last);
	if (!handle_command_path(data, cmd, tk_list->content))
		return (free_cmd(cmd));
	if (!populate_args(cmd, tk_list, tk_last) || !cmd->args)
		return (free_cmd(cmd));
	if (search_redirs(cmd, tk_list->next, tk_last))
		return (free_cmd(cmd));
	//printf("cmd builded!\n\n");
	return (cmd);
}
void	add_cmd(t_cmd **cmd_list, t_cmd *cmd)
{
	t_cmd	*tmp;

	if (!*cmd_list)
	{
		*cmd_list = cmd;
		return ;
	}
	tmp = *cmd_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cmd;
}

// Takes the token list and creates a command list.
// This function iterates through the token list, grouping tokens into commands
// based on the PIPE token. It initializes each command with its arguments,
// input/output redirections, and executable path.

// Basically it's a list with all cmds in the prompt
// and it's necessary info to execute them
t_cmd	*group_cmd(t_data *data, t_token *tk_list)
{
	t_token *tk;
	t_cmd *cmd;
	t_cmd *cmd_list;

	tk = tk_list;
	cmd_list = NULL;
	while (tk)
	{
		if (tk->type == PIPE)
		{
			cmd = build_cmd(data, tk_list, tk);
			if (cmd)
				add_cmd(&cmd_list, cmd);
			tk_list = tk->next;
		}
		tk = tk->next;
	}
	if (tk_list)
	{
		cmd = build_cmd(data, tk_list, NULL);
		if (cmd)
			add_cmd(&cmd_list, cmd);
	}
	return (cmd_list);
}
