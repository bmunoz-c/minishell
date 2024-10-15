/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:29:05 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/15 17:34:03 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"
#include "../../inc/metachars.h"
#include "../../inc/error.h"
#include "../../inc/libft/libft.h"

int	check_quotes(t_data	*data)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (data->prompt[i])
	{
		if (data->prompt[i] == '"' && s_quote % 2 == 0)
			d_quote += 1;
		if (data->prompt[i] == '\'' && d_quote % 2 == 0)
			s_quote += 1;
		i++;
	}
	if (s_quote % 2 || d_quote % 2 != 0)
		return (1);
	return (0);
}

int	check_pipe(t_data *data, char *line, int index)
{
	int	i;

	//si no es un |
	if (line[index] != PIPE[0])
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		//Si no es espacio o tab break
		if (!ft_is_space(line[i]))
			break ;
		i--;
	}
	//si es negativo
	if (i < 0)
		return (metachars_error(data, PIPE), 0);
	i = index + 1;
	//mientras exista line
	while (line[i])
	{
		//si line == ||
		if (line[i] == PIPE[0])
			return (metachars_error(data, PIPE), 0);
		else if (!ft_is_space(line[i]))
			break ;
		i++;
	}
	if (line[i] == '\0')
		return (metachars_error(data, "newline"), 0);
	return (1);
}

int	check_redirection(t_data *data, char *line, int index)
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
		if (!check_metachar(data, line, i))
			return (0);
		//Si no es espacio o tab, break
		else if (!ft_is_space(line[i]))
			break ;
		i++;
	}
	if (line [i] == '\0')
		return (metachars_error(data, "newline"), 0);
	return (1);
}

int	syntax_error(t_data *data, char *msg)
{
	data->err_code = SYNTAX_ERROR;
	data->err_msg = msg;
	return (1);
}

void	metachars_error(t_data *data, char *metachars)
{
	(void)metachars;
	data->err_code = SYNTAX_ERROR;
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
		return (syntax_error(data, QUOTE_FORMAT_ERROR));
	return (0);
}
