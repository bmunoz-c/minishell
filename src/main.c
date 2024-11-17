/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/17 23:22:09 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*int			main(int ac, char **av, char **env)
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
		if (!data.prompt)
			continue ; 
		data.token_list = NULL;
	//	write(1,"HOLAM\n", 6);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);


		tokenizer(&data, 0);
		//print_token_list(data.token_list);
		//if(!ft_strncmp(data.prompt, "printenv", 8))
		//	print_env(data.env);
		//printf("getenvvalue(%s) |%s| \n", data.prompt, get_env_value(data.env, data.prompt));
		free(data.prompt);
	}
	printf("%s\n", env[0]);
}*/

int			main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	(void)ac;
	if (ac != 1)
	{
		printf("No args are allowed\n");
		exit(1);
	}
	data.env = NULL;
	copy_env(env, &data);
	//print_env(data.env);
	while (42)
	{
		data.prompt = readline(PROMPT);
		if (!data.prompt)
			continue ;
		data.token_list = NULL;
		//write(1,"HOLAM\n", 6);
		if (!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		if(!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		tokenizer(&data, 0);
		print_token_list(data.token_list);
		expansor(&data.token_list, &data);
		print_token_list(data.token_list);
		execute(&data);
		free_ptr(data.prompt);
		free_tokens(data.token_list);
		
	}
	printf("%s\n", env[0]);
}
