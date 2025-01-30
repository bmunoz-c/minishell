/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 01:51:16 by jsebasti          #+#    #+#             */
/*   Updated: 2025/01/30 01:54:25 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_file(int *fd, char *path, int flags, int mode)
{
	if (*fd != 1 && *fd != 0 && *fd != 2)
		close(*fd);
	*fd = open(path, flags, mode);
	if (*fd < 0)
		return (1);
	return (0);
}

int	input_tokens(t_cmd *cmd, t_token *tk_list, int in_pathhand)
{
	if (tk_list->type == INPUT)
	{
		if (!tk_list->next)
			return (1);
		if (open_file(&cmd->in_fd, tk_list->next->content, O_RDONLY, 0))
		{
			perror(tk_list->next->content);
			return (1);
		}
		if (in_pathhand)
			return (2);
		return (0);
	}
	else if (tk_list->type == HERE_DOC)
	{
		if (open_file(&cmd->in_fd, HEREDOC_NAME, O_RDONLY, 0))
			return (1);
		if (in_pathhand)
			return (2);
		return (0);
	}
	return (3);
}

int	output_tokens(t_cmd *cmd, t_token *tk_list)
{
	if (tk_list->type == OUTPUT)
	{
		if (!tk_list->next)
			return (1);
		if (open_file(&cmd->out_fd, tk_list->next->content,
				O_WRONLY | O_CREAT | O_TRUNC, 0644))
			return (1);
		return (0);
	}
	else if (tk_list->type == APPEND)
	{
		if (!tk_list->next)
			return (1);
		if (open_file(&cmd->out_fd, tk_list->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0644))
		{
			perror(tk_list->next->content);
			return (1);
		}
		return (0);
	}
	return (3);
}

int	free_on_error(t_cmd *cmd, int i_args)
{
	while (i_args > 0)
		free(cmd->args[--i_args]);
	free_cmd(cmd);
	return (0);
}
