/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:04:02 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/07 20:03:35 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "metachars.h"

int	check_pipe(t_context *context, char *line, int index)
{
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
			return (syntax_error(context, PIPE), 0)
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
	if (line[index] == > && line[index + 1] == >
		|| line[index] == < && line[index + 1] == <)
	//Mientras exista line[i]
	while (line[i])
	{
		//Si no es metachar return 0
		if (!is_metachar(context, line, i))
			return (0);
		//Si no es espacio o tab, break
		else if (!is_space(line[i]))
			break ;
	}
	//Si line[i] llega al final
	if (line [i] == '\0')
		//error "newline"
		return (syntax_error(context, "newline"), 0);
	return (1);
}

int	check_syntax(t_context *context, char *line)
{

}
