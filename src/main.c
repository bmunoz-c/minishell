/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/10/31 17:39:16 by borjamc          ###   ########.fr       */
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
		print_token_list(data.token_list);
		//
		// do minishell
		//
		printf("%s\n", data.prompt);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		if(!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		free(data.prompt);
	}
	printf("%s\n", env[0]);
}*/

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
		if (!data.prompt)
			continue ; 
		data.token_list = NULL;
	//	write(1,"HOLAM\n", 6);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		printf("%s\n", data.prompt);
		if(!ft_strncmp(data.prompt, "exit", 4))
			exit(0);
		if(!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		int	index = ft_index_ch(data.prompt, '$');
		char *value = value_search(&data, data.prompt, &index);
		printf ("value: %s\n", value);

		free(data.prompt);
	}
	printf("%s\n", env[0]);
}
