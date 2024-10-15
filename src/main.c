/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/15 19:01:08 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


int			main(int ac, char **av, char **env)
{
	t_data data;
	
	(void)av;
	if(ac != 1)
	{
		printf("No args are allowed\n");
		exit(1);
	}
	while(42)
	{
		data.prompt = readline ("prompt> ");
		//
		// do minishell
		//
		printf("%s\n", data.prompt);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		free(data.prompt);
	}
	printf("%s\n", env[0]);
}
