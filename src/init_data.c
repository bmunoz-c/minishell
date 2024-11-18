/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:10 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 19:07:12 by ltrevin-         ###   ########.fr       */
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

// Initializes the t_data structure
void    init_data(t_data *data)
{
    data->prompt = NULL;
    data->env = NULL;
    data->token_list = NULL;
    data->cmd_list = NULL;
	data->path = NULL;
}