/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/18 23:12:35 by bmunoz-c         ###   ########.fr       */
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
		data.prompt = readline(PROMPT);
		if (!data.prompt)
			continue ; 
		data.token_list = NULL;
	//	write(1,"HOLAM\n", 6);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);


		tokenizer(&data, 0);
		print_token_list(data.token_list);
		//
		// do minishell
		//
		//printf("%s\n", data.prompt);
		free(data.prompt);
	}
	printf("%s\n", env[0]);
}
