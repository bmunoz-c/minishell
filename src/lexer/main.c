/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:54:57 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 19:52:03 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft/libft.h"
#include "lexer.h"
#include "../../inc/metachars.h"
/*
int	main(int ac, char **av)
{
	//t_token		*token;
	t_context	context;
	char		*line;

	(void) argv;

	if (argc > 1)
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}*/

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

int	main(int ac, char **av)
{
	int	pipe_index;
//	int	redirection_index;
	t_context	context;
	char		*line;

	if (ac >= 2)
	{
		line = av[1];
		pipe_index = index_ch(line, '|');
		if (search_ch(line, '|'))
		{
			if (check_pipe(&context, line, pipe_index))
				write(1, "ok", 2);
			else
				write(1, "ko", 2);
		}

//		if (search_ch(line))
//		check_redirection(context, line[i], index);
	}
	write(1, "\n", 1);
	return (0);
}
