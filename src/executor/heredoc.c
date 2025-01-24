/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:45:11 by jsebasti          #+#    #+#             */
/*   Updated: 2025/01/24 20:36:01 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_here(t_data *data, const char *del, int fd)
{
	int	pid;
	int	status;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		print_here(data, del, fd);
		free_data(data, 0);
		exit(0);
	}
	wait(&status);
	g_sig_exit_status = WEXITSTATUS(status);
	signal(SIGINT, handle_signal_prompt);
}

void	print_here(t_data *data, const char *del, int fd)
{
	char	*line;

	(void)data;
	line = readline("> ");
	while (line != NULL && ft_strncmp(line, del, ft_strlen(del) + 1))
	{
		ft_putendl_fd(line, fd);
		free_ptr(line);
		line = readline("> ");
	}
	free_ptr(line);
	// if (ft_strncmp(line, del, ft_strlen(del) + 1) == 0)
	// 	exit(1);
		// ft_putendl_fd(line, fd);
	// free_ptr(line);
}
