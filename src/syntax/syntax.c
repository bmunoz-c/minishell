/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:47:22 by borjamc           #+#    #+#             */
/*   Updated: 2025/01/13 22:27:40 by bmunoz-c         ###   ########.fr       */
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

// tmp->type almacena el tipo de token.
int	syntax_error_msg(t_data *data, char *ch_err)
{
	data->err_msg = ft_strdup("dancingShell: syntax error near unexpected token `");
	data->err_msg = ft_strjoin_f(data->err_msg, ch_err, 1);
	// Cerrar el mensaje con una comilla y salto de línea.
	data->err_msg = ft_strjoin_f(data->err_msg, "\'\n", 1);
	data->err_code = SYNTAX_ERROR;
	printf("%s", data->err_msg);
	return (0);
}

// 0 = EMPTY, 1 == WORD, 2 = SQ_STR, 3 = DQ_STR, 4 = PIPE.
int	syntax_pipe(t_token *tk_lst, t_data *data)
{
	t_token	*tmp;

	tmp = tk_lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			// Si no hay token previo o siguiente, syntax error
			if (!tmp->prev || !tmp->next)
				return (syntax_error_msg(data, "|"));
			else
			{
				// Si el token next & prev son
				// PIPE, INPUT, OUTPUT, APPEND, HERE_DOC, syntax error
				if ((tmp->prev->type >= 4 && tmp->prev->type <= 8)
					|| (tmp->next->type >= 4 && tmp->next->type <= 8))
					return (syntax_error_msg(data, "|"));
			}
		}
		tmp = tmp->next;
	}
	// Esto indica que la posicion de la PIPE es correcta.
	return (1);
	// probar: echo hola, > <<, >
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
		// Si el token actual es una redirección:
		if (tmp->type > 4 && tmp->type < 9)
		{
			// Si no tiene next, es un error.
			if (!tmp->next)
				return (syntax_error_msg(data, "newline"));
			// Si el siguiente token es una redirección, es un error.
			if (tmp->next->type > 4 && tmp->next->type < 9)
				return (syntax_error_msg(data, syntax_char(tmp->next)));
			// OJO ESTIII
			(void)after_heredoc;
			// if(!tmp->prev && (tmp->type != HERE_DOC || after_heredoc ))
			//	return (0);
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}
