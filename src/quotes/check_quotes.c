/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:50:50 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 17:33:32 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes/quotes.h"
#include "libft.h"

//Check '' || ""
void	check_quotes(t_quotes *quotes, char c)
{
	if (c == '\'' && !quotes->doubles)
		quotes->simple = !quotes_simple;
	else if	(c == '\"' && !quotes->simple)
		quotes->doubles = !quotes->doubles;

}

int	avoid_quotes(char *str, int	*i)
{
	char quote;

	if (str[*i] == '\"')
		quote = '\"';
	else if (str[*i] == '\'')
		quote = '\'';
	else
		return (0);
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	//no entiendo esta condicion.
	if (str[*i])
		(*i)++;
	return (1);

}

int	starting_quote(char c, t_quotes *quotes)
{
	return ((c == '\"' && !quotes->doubles) || (c == '\'' && !quotes->simple);
}
