/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:30:48 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/27 17:29:53 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		g_sig_exit_status = 0;


// TODO: call it in main before expansor.
// Add to the main data struct a fd to store the heredoc content
// add the name of the file in the prompt
void	heredoc(t_data data, const char *del, int expand)
{
	char	*line;
	int		fd;
	t_token	*tk;

	fd = open(HEREDOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	while (42)
	{
		line = readline("> ");
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
	set_sig_ignore(SIGQUIT);
	dirty_prompt = readline(PROMPT);
	if (!dirty_prompt)
		return ;
	add_history(dirty_prompt);
	data->prompt = ft_strtrim(dirty_prompt, " ");
	free(dirty_prompt);
	dirty_prompt = NULL;
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
	init_data(&data);
	copy_env(env, &data);
	//heredoc(data, "hola", 1);
	while (42)
	{
		init_signals(1);
		read_prompt(&data);
		if (!data.prompt || !*data.prompt)
			continue ;
		set_sig_ignore(SIGINT);
		tokenizer(&data, 0);
		expansor(&data.token_list, &data);
		merge_tokens(&data.token_list);
		//print_token_list(data.token_list);
		syntax_error(&data, &data.token_list);
		execute(&data);
		free_data(&data, 0);
	}
	free_data(&data, 1);
	return (EXIT_SUCCESS);
}
