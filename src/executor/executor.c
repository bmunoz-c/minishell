/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 19:10:36 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>




// // Case when it's only one command in prompt
// void run_sigle(t_cmd *cmd)
// {

// }

// // Case when there are multiple commnads in prompt
// void run_pipeline(t_cmd *cmd_list)
// {

// }

// // Run a builtin cmd
// void hanlde_builtin(t_cmd *cmd) 
// {
    
// }

void execute(t_data *data)
{
    data->cmd_list = group_cmd(data, data->token_list);
    //if(!cmd_list->next)
    //    run_sigle(cmd_list);
    //else
    //    run_pipeline(cmd_list);
    print_cmd(data->cmd_list);
}