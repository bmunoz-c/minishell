/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:04:02 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 22:07:17 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft/libft.h"
#include "lexer.h"
#include "../../inc/metachars.h"
#include "../quotes/quotes.h"

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
		//si line == ||
		if (line[i] == PIPE[0])
			return (syntax_error(context, PIPE), 0);
		else if (!is_space(line[i]))
			break ;
		i++;
	}
	if (line[i] == '\0')
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
	if ((line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]))
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

Verificar si el carácter en line[index] es un pipe:

Si el carácter en la posición index no es un pipe (|), retorna 1 (la función termina exitosamente, ya que no hay un pipe que validar).
Verificar si hay caracteres antes del pipe:

Se inicializa un índice i que comienza justo antes del índice del pipe (index - 1).
Se retrocede en la cadena verificando si hay espacios. Si encuentra algo que no sea un espacio, se detiene.
Si llega al principio de la línea sin encontrar caracteres válidos, se produce un error de sintaxis y la función retorna 0.

Verificar si hay caracteres después del pipe:

Se inicializa i en el índice inmediatamente después del pipe (index + 1).
Se avanza por la cadena de texto:
Si encuentra otro pipe inmediatamente después, retorna un error de sintaxis (dos pipes consecutivos).
Si encuentra un carácter no vacío, se detiene (el pipe es válido en esta posición).
Si llega al final de la línea sin encontrar caracteres válidos, se genera un error de sintaxis de "newline" y retorna 0.

Retorno exitoso:

Si todas las verificaciones pasan (hay caracteres válidos antes y después del pipe, y no hay dos pipes consecutivos), la función retorna 1 indicando que el uso del pipe es correcto.

Puntos clave:
Chequeo del pipe: La función verifica que un pipe no esté al principio o al final de la línea.
Chequeo de espacios: Se asegura de que no haya solo espacios en blanco antes o después del pipe.
Errores de sintaxis: Si se detectan errores (como dos pipes seguidos o un pipe al final de la línea), la función invoca syntax_error para reportarlo y retorna 0.
*/
