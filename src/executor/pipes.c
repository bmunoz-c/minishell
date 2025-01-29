/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:00:47 by jsebasti          #+#    #+#             */
/*   Updated: 2025/01/29 19:28:45 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_for_children(t_data *data, int cmd_count)
{
	int	i;
	int	exit_status;

	i = -1;
	while (++i <= cmd_count)
		wait(&exit_status);
	if (WIFEXITED(exit_status))
		data->err_code = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGINT)
		{
			printf("\n");
			data->err_code = 130;
		}
		else if (WTERMSIG(exit_status) == SIGQUIT)
		{
			printf("Quit (Core dumped)\n");
			data->err_code = 131;
		}
	}
}

void	asign_in_out(int *pipefd, t_cmd *cmd_list, int cmd_count)
{
	if (cmd_list->in_fd != 0)
		dup2(cmd_list->in_fd, STDIN_FILENO);
	if (cmd_count > 0 && cmd_list->in_fd == 0)
		dup2(pipefd[cmd_count * 2 - 2], STDIN_FILENO);
	if (cmd_list->out_fd != 1)
		dup2(cmd_list->out_fd, STDOUT_FILENO);
	if (cmd_list->next)
		dup2(pipefd[cmd_count * 2 + 1], STDOUT_FILENO);
}

void	close_all_pipes(int *pipefd, int count_pipes)
{
	int	i;

	i = 0;
	while (i < count_pipes * 2)
	{
		close(pipefd[i]);
		i++;
	}
	free_ptr(pipefd);
}

void	create_pipes(int *pipefd, int count_pipes)
{
	int	i;

	i = 0;
	while (i < count_pipes)
	{
		if (pipe(pipefd + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	dup_fds(int new_in, int new_out, int old_in, int old_out)
{
	dup2(new_in, old_in);
	dup2(new_out, old_out);
}
