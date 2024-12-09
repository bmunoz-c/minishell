/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/09 20:36:40 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>




/* // Case when it's only one command in prompt
void run_sigle(t_data data, t_cmd *cmd)
{
	if(cmd->builtin)
		hanlde_builtin(data, cmd);
	else
	{
		// execb
		
	}
}

// Case when there are multiple commnads in prompt
void run_pipeline(t_data data, t_cmd *cmd)
{
	
}

// Run a builtin cmd
void hanlde_builtin(t_data data, t_cmd *cmd) 
{
	
} */


void execute(t_data *data)
{
    data->cmd_list = group_cmd(data, data->token_list);
/*     if(!data->cmd_list->next)
        run_sigle(data, data->cmd_list);
    else
        run_pipeline(data, data->cmd_list); */
    print_cmd(data->cmd_list);
}
