/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:47:22 by borjamc           #+#    #+#             */
/*   Updated: 2025/01/23 16:03:06 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*syntax_char(t_token *tmp)
{
	if (tmp->type == PIPE)
		return ("|");
	else if (tmp->type == HERE_DOC)
		return ("<<");
	else if (tmp->type == OUTPUT)
		return (">");
	else if (tmp->type == APPEND)
		return (">>");
	else if (tmp->type == INPUT)
		return ("<");
	return (NULL);
}

/*
- tmp->type almacena el tipo de token.
- 39: Cerrar el mensaje con una comilla y salto de línea.
*/
int	syntax_error_msg(t_data *data, char *ch_err)
{
	data->err_msg = ft_strdup(SYNT_ERR_UN_T);
	data->err_msg = ft_strjoin_f(data->err_msg, ch_err, 1);
	data->err_msg = ft_strjoin_f(data->err_msg, "\'\n", 1);
	data->err_code = SYNTAX_ERROR;
	printf("%s", data->err_msg);
	return (0);
}

/*
- 0 = EMPTY, 1 == WORD, 2 = SQ_STR, 3 = DQ_STR, 4 = PIPE.
- Return 1 if the pipe is in the correct position.
*/
int	syntax_pipe(t_token *tk_lst, t_data *data)
{
	t_token	*tmp;

	tmp = tk_lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->prev || !tmp->next)
				return (syntax_error_msg(data, "|"));
			else
			{
				if ((tmp->prev->type >= 4 && tmp->prev->type <= 8)
					|| (tmp->next->type >= 4 && tmp->next->type <= 8))
					return (syntax_error_msg(data, "|"));
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

// HERE_DOC > 16 mensaje de error (BASH) en el main.
int	here_doc_error(t_data *data)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
		return (0);
	return (1);
}

/*
- Si el token actual es una redirección:
	- Si no tiene next, es un error.
	- Si el siguiente token es una redirección, es un error.
	- Si el token actual es una redirección y no tiene prev, es un error.
*/
int	syntax_error(t_data *data, t_token **token, int after_heredoc)
{
	t_token	*tmp;

	tmp = *token;
	// TODO: quitar el 16
	if (!here_doc_error(data))
		return (syntax_error_msg(data, "<<16"));
	if (!syntax_pipe(tmp, data))
		return (0);
	while (tmp)
	{
		if (tmp->type > 4 && tmp->type < 9)
		{
			if (!tmp->next)
				return (syntax_error_msg(data, "newline"));
			if (tmp->next->type > 4 && tmp->next->type < 9)
				return (syntax_error_msg(data, syntax_char(tmp->next)));
			// OJO ESTO
			(void)after_heredoc;
			// if(!tmp->prev && (tmp->type != HERE_DOC || after_heredoc ))
			//	return (0);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
