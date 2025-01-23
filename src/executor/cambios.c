/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cambios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:41:35 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/23 17:00:01 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	open_file(int *fd, char *path, int flags, int mode)
{
	*fd = open(path, flags, mode);
	if (*fd < 0)
		return (1);
	return (0);
}

/*
- Cambios realizados:
- Creación de la función auxiliar open_file:
- Validacion de tk_list->next.
- Cierre de descritores existentes.
- Uso de flags para compactar la logica de OUTPUT, APPEND.
*/
int	search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last)
{
	int	flags;

	while (tk_list != tk_last)
	{
		if (tk_list->type == INPUT)
		{
			if (!tk_list->next)
				return (1);
			if (open_file(&cmd->in_fd, tk_list->next->content, O_RDONLY, 0))
				return (1);
			tk_list = tk_list->next;
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
				return (1);
			tk_list = tk_list->next;
		}
		else if (tk_list->type == HERE_DOC)
		{
			if (open_file(&cmd->in_fd, HEREDOC_NAME, O_RDONLY, 0))
				return (1);
		}
		tk_list = tk_list->next;
	}
	return (0);
}
