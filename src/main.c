/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/12 20:05:24 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <minishell.h>

int sig_exit_status = 0;



int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*dirty_prompt;

	(void)av;
	if (ac != 1)
	{
		printf("No args are allowed\n");
		exit(1);
	}
	init_data(&data);
	copy_env(env, &data);
	while (42)
	{
		init_signals(1);
		set_sig_ignore(SIGQUIT);
		dirty_prompt = readline(PROMPT);
		if (!dirty_prompt)
			continue ;
		data.prompt = ft_strtrim(dirty_prompt, " ");
		free(dirty_prompt);
		dirty_prompt = NULL;
		if (!data.prompt)
			continue ;
		if (!ft_strncmp(data.prompt, "exit", 4))
			break ;
		if (!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		printf("prompt: %s\n", data.prompt);
		set_sig_ignore(SIGINT);
		tokenizer(&data, 0);
		//print_token_list(data.token_list);
		expansor(&data.token_list, &data);
		merge_tokens(&data.token_list);
		print_token_list(data.token_list);
		syntax_error(&data, &data.token_list);		
		execute(&data);
		//ft_free_split(array);
		free_data(&data, 0);
	}
	free_data(&data, 1);
	return (EXIT_SUCCESS);
}
