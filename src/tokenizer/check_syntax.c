/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:29:05 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 18:54:10 by bmunoz-c         ###   ########.fr       */
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

int	check_pipe(t_data *data, char *line, int index)
{
	int	i;

	if (line[index] != PIPE[0])
		return (1);
	i = index - 1;
	while (i >= 0)
	{
		if (!ft_is_space(line[i]))
			break ;
		i--;
	}
	if (i < 0)
		return (metachars_error(data, PIPE), 0);
	i = index + 1;
	while (line[i])
	{
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

	if (!is_redirection(line, index))
		return (1);
	i = index + 1;
	if ((line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]))
		i++;
	while (line[i])
	{
		if (!check_metachar(data, line, i))
			return (0);
		else if (!ft_is_space(line[i]))
			break ;
		i++;
	}
	if (line [i] == '\0')
		return (metachars_error(data, "newline"), 0);
	return (1);
}

int	check_syntax(t_data *data)
{
	if (check_quotes(data))
		return (syntax_error(data, QUOTE_FORMAT_ERROR));
	return (0);
}
