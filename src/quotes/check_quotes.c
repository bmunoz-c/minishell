/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:50:50 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/11 21:20:23 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes/quotes.h"
#include "../../inc/error.h"
#include "libft.h"

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

static int	syntax_error(t_data *data, char *msg)
{
	data->err_code = SYNTAX_ERROR;
	data->err_msg = msg;
	return (1);
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
		return (syntax_error(data, QUOTE_FORMAT_ERROR));
	return (0);
}
