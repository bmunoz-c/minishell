/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 02:34:18 by jsebasti          #+#    #+#             */
/*   Updated: 2025/01/31 08:54:21 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	save_args(t_cmd *cmd, int *i_args, char *content)
{
	cmd->args[*i_args] = ft_strdup(content);
	if (!cmd->args[*i_args])
		return (free_on_error(cmd, *i_args));
	*i_args += 1;
	return (0);
}

int	check_builtin(t_cmd *cmd, char *content, int flag)
{
	if (ft_strncmp(content, "echo", 5) == 0 || ft_strncmp(content, "cd", 3) == 0
		|| ft_strncmp(content, "pwd", 4) == 0 || ft_strncmp(content, "export",
			7) == 0 || ft_strncmp(content, "unset", 6) == 0
		|| ft_strncmp(content, "env", 4) == 0 || ft_strncmp(content, "exit",
			5) == 0)
	{
		cmd->builtin = 1;
		cmd->path = ft_strdup(content);
		return (flag);
	}
	return (0);
}

int	check_relative_cmd(t_cmd *cmd, t_data *data, char *content)
{
	cmd->path = search_in_env(data, content);
	cmd->args[0] = ft_strdup(cmd->path);
	cmd->args[1] = NULL;
	if (!cmd->path)
	{
		ft_putstr_fd(content, 2);
		ft_putstr_fd(CMDNOTFND, 2);
		data->err_code = 127;
		return (0);
	}
	return (1);
}

void	create_cmd(t_data *data, t_token *tk_list, t_token *tk_last,
		t_cmd **cmd_list)
{
	t_cmd	*cmd;

	cmd = build_cmd(data, tk_list, tk_last);
	if (cmd)
		add_cmd(cmd_list, cmd);
}
