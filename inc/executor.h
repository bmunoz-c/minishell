/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:05:32 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/19 11:57:29 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




// Cmd list utils
t_cmd	*group_cmd(t_data *data, t_token *tk_list);
void execute(t_data *data);
int	handle_command_path(t_data *data, t_cmd *cmd, char *content);