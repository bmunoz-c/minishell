/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/29 10:36:51 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		g_sig_exit_status = 0;

void	read_prompt(t_data *data)
{
	char	*dirty_prompt;

	dirty_prompt = readline(PROMPT);
	if (!dirty_prompt)
		exit(127);
	add_history(dirty_prompt);
	data->prompt = ft_strtrim(dirty_prompt, " ");
	free(dirty_prompt);
	dirty_prompt = NULL;
	if (!data->prompt)
		printf("Error: ft_strtrim faied to allocate mem\n");
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)av;
	if (ac != 1)
	{
		printf("No args are allowed\n");
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal_prompt);
	init_data(&data);
	copy_env(env, &data);
	while (42)
	{
		read_prompt(&data);
		// BORJA
		if (!data.prompt || !*data.prompt)
		{
			free(data.prompt);
			data.prompt = NULL;
			continue ;
		}
		tokenizer(&data, 0);
		if (syntax_error(&data, &data.token_list, 0))
		{
			if (check_heredoc(data.token_list, &data))
			{
				expansor(&data.token_list, &data);
				merge_tokens(&data.token_list);
				if (syntax_error(&data, &data.token_list, 1))
					execute(&data);
			}
		}
		free_data(&data, 0);
	}
	free_data(&data, 1);
	return (EXIT_SUCCESS);
}
