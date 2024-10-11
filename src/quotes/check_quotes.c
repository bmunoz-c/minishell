/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:50:50 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/11 20:40:33 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes/quotes.h"
#include "libft.h"

/*
//Check '' || ""
void	check_quotes(t_quotes *quotes, char c)
{
	if (c == '\'' && !quotes->doubles)
		quotes->simple = !quotes_simple;
	else if	(c == '\"' && !quotes->simple)
		quotes->doubles = !quotes->doubles;
}
*/

int	check_quotes(t_data	*data)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (t_data->prompt[i])
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

void	syntax_error(t_context *context)
{
	context->error_code = SYNTAX_ERROR;
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
		syntax_error(data)

	
	if (da)
	{
		//salir
		//printar error
		return (1);

	}
	return (0);
}
