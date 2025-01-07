/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:10 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/07 16:09:02 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Initializes the t_cmd structure and counts the number of arguments
void	init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last)
{
	cmd->path = NULL;
	cmd->in_fd = STDIN_FILENO;
	cmd->out_fd = STDOUT_FILENO;
	cmd->next = NULL;
	cmd->nargs = 0;
	cmd->args = NULL;
	cmd->append_output = 0;
	cmd->builtin = 0;
	while (tk_first != tk_last)
	{
		if (tk_first->type == WORD || tk_first->type == DQ_STR || tk_first->type == SQ_STR)
			cmd->nargs++;
		else
			break;
		tk_first = tk_first->next;
	}
	cmd->args = ft_calloc(sizeof(char *) * (cmd->nargs + 1), 1);
}

// Initializes the t_data structure
void    init_data(t_data *data)
{
    data->prompt = NULL;
    data->env = NULL;
    data->token_list = NULL;
    data->cmd_list = NULL;
	data->path = NULL;
	data->env_matrix = NULL;
	data->err_code = 0;
	data->err_msg = NULL;
}