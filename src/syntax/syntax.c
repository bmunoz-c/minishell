/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:47:22 by borjamc           #+#    #+#             */
/*   Updated: 2024/12/03 00:14:37 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//
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

//tmp->type almacena el tipo de token,
//exit almacena el valor de salida
//data->exit almacena el valor de salida
//error almacena el tipo de error
//a. Si `1`: Imprimir `|`.
//b. Si `2`: Imprimir `newline`.
//c. Si `3`: Usar `ft_syntax_char(tmp)` para obtener el token relacionado.
int	syntax_error_msg(t_data *data, t_token *tmp, int error, int exit)
{
	ft_putstr_fd("minihell: syntax error near unexpected token `", 2);
	if (error == 1)
		ft_putstr_fd("|", 2);
	if (error == 2)
		ft_putstr_fd("newline", 2);
	if (error == 3)
		ft_putstr_fd(ft_syntax_char(tmp), 2);
    //Cerrar el mensaje con una comilla y salto de línea.
	ft_putstr_fd("\'\n", 2);
    //Anadir exit en la estructura data.
    //Actualizar data->exit con el valor de `exit`.
	data->exit = exit;
	return (0);
}

//0 = EMPTY, 1 == WORD, 2 = SQ_STR, 3 = DQ_STR, 4 = PIPE.
int	syntax_pipe(t_token *tmp, t_data *data)
{
    //Si es PIPE.
	if (tmp->type == 4)
	{
        //Si no hay token previo o siguiente, syntax error
		if (!tmp->prev || !tmp->next)
			return (ft_print_syntax_error(data, tmp, 1, 258));
            //El código de error 258 se asigna a data->exit.
		if (tmp->prev && tmp->next)
		{
            //Si el token next & prev son
            //PIPE, INPUT, OUTPUT, APPEND, HERE_DOC, syntax error
			if (tmp->prev->type >= 4 && tmp->prev->type <= 8)
				return (ft_print_syntax_error(data, tmp, 1, 258));
			if (tmp->prev->type == 0)
			{
                //Si no hay un token anterior al token previo, error
    			if (!tmp->prev->prev)
					return (ft_print_syntax_error(data, tmp, 1, 258));
                //Si el tipo del token anterior al token previo
                //está entre 5 y 8, también es inválido.
                //INPUT, OUTPUT, APPEND, HERE_DOC
				if (tmp->prev->prev->type >= 5 && tmp->prev->prev->type <= 8)
					return (ft_print_syntax_error(data, tmp, 1, 258));
			}
		}
	}
    //Esto indica que la posicion de la PIPE es correcta.
	return (1);
    //probar: echo hola, > <<, >
}

//Checkea redirecciones
int	syntax_redirs(t_token **tmp)
{
    //(*tmp) representa el token actual que estamos comprobando.
     //Si (*tmp)->next->type esta vacío y no hay otro token después, es inválido.

	if ((*tmp)->next && (*tmp)->next->type == 0 && !(*tmp)->next->next)
		return (0);
        //ex: echo >
    //Si (*tmp)->next->type esta vacío y hay otro token después que sea
    //WORD, SQ o DQ, es invalido.
	if ((*tmp)->next && (*tmp)->next->type == 0 && (*tmp)->next->next
		&& ((*tmp)->next->next->type < 1 || (*tmp)->next->next->type > 3))
        //ex: echo > | grep foo
		return (0);
    //Si (*tmp)->next->type no esta vacio, es invalido.
	if ((*tmp)->next && (*tmp)->next->type != 0)
		return (0);
        //ex: echo >|
    //Si (*tmp)->type es > && (*tmp)->next es <<, es inválido
	if ((*tmp)->type == 6 && (*tmp)->next && (*tmp)->next->type == 8)
		return (0);
        //ex: echo > <<
	return (1);
}

int	ft_syntax_error(t_data *data, t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
        //Si encuentra un error de sintaxis relacionado con un pipe, retorna 0.
		if (!ft_syntax_pipe(tmp, data))
			return (0);
        //Si tmp es una redirección y no tiene next, es un error.
		if (!tmp->next && (tmp->type >= 5 && tmp->type <= 8))
			return (ft_print_syntax_error(data, tmp, 2, 258));
        //Si el token actual es una redirección:
		if (tmp->type > 4 && tmp->type < 9)
		{
            //Si hay un error, muestra el mensaje y retorna 0.
			if (!ft_syntax_redirs(&tmp))
				return (ft_print_syntax_error(data, tmp, 3, 258));
            //Llama a parse_redirs para procesar la redirección
            //(por ejemplo, asignar archivos o manejar heredocs).
			if (!parse_redirs(data, &tmp))
				return (ft_print_syntax_error(data, tmp, 2, 258));
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

