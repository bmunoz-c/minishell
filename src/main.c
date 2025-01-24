/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/24 17:41:27 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		g_sig_exit_status = 0;

// TODO: call it in main before expansor.
// Add to the main data struct a fd to store the heredoc content
// add the name of the file in the prompt.
// HE ARREGLADO EL ERROR DE HEREDOC CON CONTRL D, linea 32 y 32.
void	heredoc(t_data data, const char *del, int expand)
{
	char	*line;
	int		fd;
	t_token	*tk;

	// TODO
	printf("Expandir: %d\n", expand);
	fd = open(HEREDOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	signal(SIGINT, heredoc_handler);
	while (42)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
			break ;
		if (expand)
		{
			tk = new_token(ft_strdup(line), WORD);
			expansor(&tk, &data);
			free_ptr(line);
			if (tk)
				line = ft_strdup(tk->content);
			free_token(tk);
		}
		ft_putendl_fd(line, fd);
		free_ptr(line);
	}
	free_ptr(line);
	close(fd);
}

void	read_prompt(t_data *data)
{
	char	*dirty_prompt;

	printf(RED "$?: %d\n" RESET, data->err_code);
	// set_sig_ignore(SIGQUIT);
	signal(SIGQUIT, handle_signal_prompt);
	dirty_prompt = readline(PROMPT);
	if (!dirty_prompt)
		exit(127);
	add_history(dirty_prompt);
	/* if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	} */
	data->prompt = ft_strtrim(dirty_prompt, " ");
	free(dirty_prompt);
	dirty_prompt = NULL;
	if (!data->prompt)
		printf("Error: ft_strtrim faied to allocate mem\n");
}

int	check_heredoc(t_token *tk_lst, t_data *data)
{
	t_token	*tk;
	t_token	*del;

	tk = tk_lst;
	while (tk)
	{
		if (tk->type == HERE_DOC)
		{
			del = tk->next;
			while (del->type == SPC)
				del = del->next;
			// TODO: chequear cuando hay comillas despues del word, en el del.
			if (del->type != WORD && del->type != DQ_STR && del->type != SQ_STR)
			{
				syntax_error_msg(data, "heredoc");
				return (0);
			}
			printf("heredoc: |%s|\n", del->content);
			printf("heredoc: |%i|\n", del->type);
			heredoc(*data, del->content, del->type == WORD);
		}
		tk = tk->next;
	}
	return (1);
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
				print_token_list(data.token_list);
				printf("#################################\n");
				expansor(&data.token_list, &data);
				print_token_list(data.token_list);
				printf("#################################\n");
				merge_tokens(&data.token_list);
				print_token_list(data.token_list);
				if (syntax_error(&data, &data.token_list, 1))
				{
					printf("Intento ejecutar\n");
					execute(&data);
				}
			}
		}
		free_data(&data, 0);
	}
	free_data(&data, 1);
	return (EXIT_SUCCESS);
}
