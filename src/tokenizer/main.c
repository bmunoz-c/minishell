/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:37:31 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 18:55:18 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	search_ch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

int	index_ch(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}

//check 1 PIPE
int	main(int ac, char **av)
{
	int		pipe_index;
//	int	redirection_index;
	t_data		data;
	char		*line;

	if (ac >= 2)
	{
		line = av[1];
		pipe_index = index_ch(line, '|');
		if (search_ch(line, '|'))
		{
			if (check_pipe(&data, line, pipe_index))
				write(1, "ok", 2);
			else
				write(1, "ko", 2);
		}

//		if (searline, '|'ch_ch(line))
//		check_redirection(context, line[i], index);
	}
	write(1, "\n", 1);
	return (0);
}

