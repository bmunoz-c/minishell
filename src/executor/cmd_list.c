/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:18:25 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/11 03:33:35 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Initializes the t_cmd structure and counts the number of arguments
void	init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last)
{
	cmd->path = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->next = NULL;
	cmd->nargs = 0;
	while (tk_first != tk_last)
	{
		if (tk_first->type == WORD || tk_first->type == SPC)
			cmd->nargs++;
		tk_first = tk_first->next;
	}
	cmd->args = malloc(sizeof(char *) * (cmd->nargs + 1));
}

// Handles the command path search and returns whether it was successful
int	handle_command_path(t_cmd *cmd, char *content)
{
	cmd->path = search_cmd_path(content);
	if (!cmd->path)
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}

// Fills the command arguments array
int	populate_args(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	int	i_args;

	i_args = 0;
	while (tk_list != tk_last)
	{
		if (tk_list->type == WORD || tk_list->type == SPC)
		{
			cmd->args[i_args] = ft_strdup(tk_list->content);
			if (!cmd->args[i_args])
			{
				free_cmd(cmd);
				return (0); // Memory allocation failed
			}
			i_args++;
		}
		tk_list = tk_list->next;
	}
	cmd->args[i_args] = NULL; // Null-terminate the array
	return (1);
}

// Handles input and output redirections
int	search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	while (tk_list != tk_last)
	{
		if (tk_list->type == INPUT)
		{
			cmd->input_file = ft_strdup(tk_list->next->content);
			if (!cmd->input_file)
				break ;
			tk_list = tk_list->next;
		}
		else if (tk_list->type == OUTPUT)
		{
			cmd->output_file = ft_strdup(tk_list->next->content);
			if (!cmd->output_file)
				break ;
			tk_list = tk_list->next;
		}
		// TODO: Handle other redirection types like REDIR and HERE_DOC
		tk_list = tk_list->next;
	}
	if (tk_list != tk_last) // We broke the loop so it's malloc failure
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}

// Main function to build the command structure
t_cmd	*build_cmd(t_data *data, t_token *tk_list, t_token *tk_last)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_data(cmd, tk_list->next, tk_last);
	if (!cmd->args)
		return (free_cmd(cmd));
	if (!handle_command_path(cmd, tk_list->content))
		return (free_cmd(cmd));
	if (!populate_args(cmd, tk_list->next, tk_last))
		return (free_cmd(cmd));
	if (!search_redirs(cmd, tk_list->next, tk_last))
		return (free_cmd(cmd));
	return (cmd);
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
			cmd = build_cmd(data, tk_list, tk);
			add_cmd(&cmd_list, cmd);
		}
		tk = tk->next;
	}
	// There is no pipes so it's only one command
	if (!cmd_list)
	{
		cmd = build_cmd(data, tk_list, tk);
		add_cmd(&cmd_list, cmd);
	}
	return (cmd_list);
}
