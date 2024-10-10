/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:04:02 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 19:01:52 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer/lexer.h"
#include "metachars.h"
#include "quotes/quotes.h"

int	is_space(char c)
{
	return (c == '\t' || c == ' ');
}

int	check_pipe(t_context *context, char *line, int index)
{
	int	i;

	//si no es un |
	if (line[index] != PIPE[0])
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		//Si no es espacio o tab break
		if (!is_space(line[i]))
			break ;
		i--;
	}
	//si es negativo
	if (i < 0)
		return (syntax_error(context, PIPE), 0);
	i = index + 1;
	//mientras exista line
	while (line[i])
	{
		//si line == |
		if (line[i] == PIPE[0])
			//ERROR
			return (syntax_error(context, PIPE), 0);
		else if (!is_space(line[i]))
			break ;
		i++;
	}
	//si llega al final
	if (line[i] == '\0')
		//ERROR
		return (syntax_error(context, "newline"), 0);
	return (1);
}

int	check_redirection(t_context *context, char *line, int index)
{
	int	i;

	//si no es redirection, return (1);
	if (!is_redirection(line, index))
		return (1);
	i = index + 1;
	//Si line[index] == <> || <<>>, i++;
	if (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0])
		i++;
	//Mientras exista line[i]
	while (line[i])
	{
		//Si no es metachar return 0
		if (!check_metachar(context, line, i))
			return (0);
		//Si no es espacio o tab, break
		else if (!is_space(line[i]))
			break ;
		i++;
	}
	//Si line[i] llega al final
	if (line [i] == '\0')
		return (syntax_error(context, "newline"), 0);
	return (1);
}
/*
int	check_syntax(t_context *context, char *line)
{
	t_quotes_flag	quotes;
	int				i;

	i = 0;
	//mientras line[i] exista {
	//chequear quotes
	//si no son quotes.dobles, ni son quotes.simples, ni es PIPE, return (0);
	//si no son quotes dobles, ni son quotes.simples, ni son redirecciones, return(0);
	//i++; }

	//si son quotes.dobles, ERROR D_QUOTE
	//si son quotes.simples, ERROR S_QUOTE
	//return (1);
}*/

/*
***APUNTES***
- t_context almacena la informacion de errores del procesamiento.
- char *line es la cadena de texto que representa la linea de comando.
- index es el indice donde se encuentra el simbolo (|)
- ret 1 si la validación es exitosa (uso correcto del pipe).
- ret 0 si hay un error de sintaxis relacionado con el pipe.
*/
