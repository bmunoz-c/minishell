/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:54:57 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 17:41:54 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer/lexer.h"
#include "metachars.h"
i/*
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

int	main(inc ac, char **av)
{
	int	i;
	t_context	context;
	char		*line;

	if (ac >= 1)
	{
		i = 0;
		line = av[1];
		check_pipe(context, line[i], index);
		check_redirection(context, line[i], index);
	}
	write(1, "\n", 1);
	return (0);
}
