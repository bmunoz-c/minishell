/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:18:25 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/31 08:54:27 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
// Fills the command arguments array. (Validacion, iteracion, finalizacion).
- TODO: He añadido un if en la linea 34.
- TODO: He modificado el if de la 47 par acortar lineas.
- TODO: He creado free_on_error para acortar la funcion. Usada en la 49.
*/
int	populate_args(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	int	i_args;
	int	redir;

	redir = 0;
	if (!cmd || !cmd->args || !tk_list)
		return (0);
	i_args = 0;
	if (cmd->args[0])
	{
		i_args = 1;
		tk_list = tk_list->next;
	}
	while (tk_list != tk_last)
	{
		if ((tk_list->type == WORD || tk_list->type == SQ_STR
				|| tk_list->type == DQ_STR) && redir == 0)
			save_args(cmd, &i_args, tk_list->content);
		else
			redir = !redir;
		tk_list = tk_list->next;
	}
	cmd->args[i_args] = NULL;
	return (1);
}

int	search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last,
		int in_pathhand)
{
	static int	ret = 0;

	while (tk_list != tk_last)
	{
		if (tk_list->type == PIPE)
			break ;
		ret = input_tokens(cmd, tk_list, in_pathhand);
		if (ret == 1 || ret == 2)
			return (ret);
		if (ret == 0)
		{
			tk_list = tk_list->next->next;
			continue ;
		}
		ret = output_tokens(cmd, tk_list);
		if (ret == 1)
			return (ret);
		if (ret == 0)
			tk_list = tk_list->next;
		tk_list = tk_list->next;
	}
	return (0);
}

// Main function to build the command structure
t_cmd	*build_cmd(t_data *data, t_token *tk_list, t_token *tk_last)
{
	t_cmd	*cmd;
	int		input;

	cmd = ft_calloc(sizeof(t_cmd), 1);
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

t_cmd	*group_cmd(t_data *data, t_token *tk_list)
{
	t_cmd	*cmd_list;
	t_token	*tk;

	tk = tk_list;
	cmd_list = NULL;
	while (tk)
	{
		if (tk->type == PIPE)
		{
			create_cmd(data, tk_list, tk, &cmd_list);
			tk_list = tk->next;
		}
		if (tk->type == HERE_DOC)
			tk = tk->next;
		tk = tk->next;
	}
	if (tk_list)
		create_cmd(data, tk_list, NULL, &cmd_list);
	return (cmd_list);
}
