/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:18:25 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/29 19:30:00 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	free_on_error(t_cmd *cmd, int i_args)
{
	while (i_args > 0)
		free(cmd->args[--i_args]);
	free_cmd(cmd);
	return (0);
}

/*
// Fills the command arguments array. (Validacion, iteracion, finalizacion).
- TODO: He añadido un if en la linea 34.
- TODO: He modificado el if de la 47 par acortar lineas.
- TODO: He creado free_on_error para acortar la funcion. Usada en la 49.
*/
int	populate_args(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	int	i_args;

	if (!cmd || !cmd->args || !tk_list)
		return (0);
	i_args = 0;
	if (cmd->args[0])
	{
		i_args = 1;
		if (tk_list->type != HERE_DOC)
			tk_list = tk_list->next;
	}
	while (tk_list != tk_last)
	{
		if (tk_list->type == 1 || tk_list->type == 2 || tk_list->type == 3)
		{
			cmd->args[i_args] = ft_strdup(tk_list->content);
			if (!cmd->args[i_args])
				return (free_on_error(cmd, i_args));
			i_args++;
		}
		else if (tk_list->type == HERE_DOC)
		{
			cmd->args[i_args] = ft_strdup(HEREDOC_NAME);
			if (!cmd->args[i_args])
				return (free_on_error(cmd, i_args));
			i_args++;
			break ;
		}
		else
			break ;
		tk_list = tk_list->next;
	}
	cmd->args[i_args] = NULL;
	return (1);
}

int	open_file(int *fd, char *path, int flags, int mode)
{
	if (*fd != 1 && *fd != 0 && *fd != 2)
		close(*fd);
	*fd = open(path, flags, mode);
	if (*fd < 0)
		return (1);
	return (0);
}

int	search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last, int in_pathhand)
{
	while (tk_list != tk_last)
	{
		if (tk_list->type == PIPE)
			break ;
		if (tk_list->type == INPUT)
		{
			if (!tk_list->next)
				return (1);
			if (open_file(&cmd->in_fd, tk_list->next->content, O_RDONLY, 0))
			{
				perror(tk_list->next->content);
				return (1);
			}
			tk_list = tk_list->next;
			if (in_pathhand)
				return (2);
		}
		else if (tk_list->type == OUTPUT)
		{
			if (!tk_list->next)
				return (1);
			if (open_file(&cmd->out_fd, tk_list->next->content,
					O_WRONLY | O_CREAT | O_TRUNC, 0644))
				return (1);
			tk_list = tk_list->next;
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
			tk_list = tk_list->next;
		}
		else if (tk_list->type == HERE_DOC)
		{
			if (open_file(&cmd->in_fd, HEREDOC_NAME, O_RDONLY, 0))
			{
				perror(tk_list->next->content);
				return (1);
			}
			if (in_pathhand)
				return (2);
		}
		tk_list = tk_list->next;
	}
	return (0);
}

// Main function to build the command structure
t_cmd	*build_cmd(t_data *data, t_token *tk_list, t_token *tk_last)
{
	t_cmd	*cmd;
	int		input;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	init_cmd_data(cmd, tk_list, tk_last);
	input = handle_command_path(data, cmd, tk_list->content, tk_list);
	if (input == 0)
		return (free_cmd(cmd));
	else if (input == 2)
	{
		while (tk_list->type == INPUT || tk_list->type == HERE_DOC)
			tk_list = tk_list->next->next;
	}
	if (!populate_args(cmd, tk_list, tk_last) || !cmd->args)
		return (free_cmd(cmd));
	if (search_redirs(cmd, tk_list->next, tk_last, 0))
		return (free_cmd(cmd));
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
	tmp->next->next = NULL;
}

// Takes the token list and creates a command list.
// This function iterates through the token list, grouping tokens into commands
// based on the PIPE token. It initializes each command with its arguments,
// input/output redirections, and executable path.
// Basically it's a list with all cmds in the prompt
// and it's necessary info to execute them
t_cmd	*group_cmd(t_data *data, t_token *tk_list)
{
	t_token	*tk;
	t_cmd	*cmd;
	t_cmd	*cmd_list;

	tk = tk_list;
	cmd_list = NULL;
	while (tk)
	{
		if (tk->type == HERE_DOC)
		{
			tk = tk->next->next;
			continue ;
		}
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
