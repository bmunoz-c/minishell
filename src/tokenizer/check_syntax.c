/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:29:05 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 20:19:23 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
		return (syntax_error(data, QUOTE_FORMAT_ERROR));
	return (0);
}
