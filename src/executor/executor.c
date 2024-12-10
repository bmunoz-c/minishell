/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/10 12:22:25 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// Run a builtin cmd
void hanlde_builtin(t_data *data, t_cmd *cmd) 
{
	(void)data;
	(void)cmd;
	//if (ft_strncmp(cmd->path, "echo", 5) == 0)
		//run_echo(cmd->args);
	// else if (ft_strncmp(cmd->path, "cd", 3) == 0)
	// else if (ft_strncmp(cmd->path, "pwd", 4) == 0)
	// else if (ft_strncmp(cmd->path, "export", 7) == 0)
	// else if (ft_strncmp(cmd->path, "unset", 6) == 0)
	// else if (ft_strncmp(cmd->path, "env", 4) == 0)
	// else if (ft_strncmp(cmd->path, "exit", 5) == 0))
}

// Case when it's only one command in prompt
void run_sigle(t_data *data, t_cmd *cmd)
{
	if(cmd->builtin)
		hanlde_builtin(data, cmd);
	else
	{
		// execb
		(void)data;
	}
}

// Case when there are multiple commnads in prompt
void run_pipeline(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;	
}




void execute(t_data *data)
{
    data->cmd_list = group_cmd(data, data->token_list);
	print_cmd(data->cmd_list);
	if(!data->cmd_list)
		return ;
	if(!data->cmd_list->next)
		run_sigle(data, data->cmd_list);
    else
		run_pipeline(data, data->cmd_list);
}
