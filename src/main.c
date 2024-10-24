/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/24 13:46:10 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int			main(int ac, char **av, char **env)
{
	t_data data;
	
	(void)av;
	(void)ac;
	if(ac != 1)
	{
		printf("No args are allowed\n");
		exit(1);
	}
	data.env = NULL;
	copy_env(env, &data);
	//print_env(data.env);
	while(42)
	{
		data.prompt = readline(PROMPT);
		//
		// do minishell
		//
		printf("%s\n", data.prompt);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		if(!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		printf("getenvvalue(%s) |%s| \n", data.prompt, get_env_value(data.env, data.prompt));
		free(data.prompt);
	}
	free_env(data.env);
	printf("%s\n", env[0]);
}
