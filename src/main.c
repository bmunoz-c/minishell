/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 13:58:11 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


//HERE_DOC > 16 mensaje de error (BASH) en el main.
int	here_doc_error(t_data *data)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = data->token_list;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			count++;
		tmp = tmp->next;
	}
	if (count > 16)
	{
		printf("bash: syntax error near unexpected token `<<'\n");
		return (1);
	}
	return (0);
}

int			main(int ac, char **av, char **env)
{
	t_data	data;

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
		data.prompt = readline(PROMPT);
		if (!data.prompt)
			continue ;
		if (!ft_strncmp(data.prompt, "exit", 4))
			break ;
		if (!ft_strncmp(data.prompt, "printenv", 8))
			print_env(data.env);
		tokenizer(&data, 0);
		expansor(&data.token_list, &data);
		if (here_doc_error(&data))
			continue ;
		execute(&data);
		free_data(&data, 0);
	}
	free_data(&data, 1);
}
