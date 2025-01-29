/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/29 14:33:15 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_fds(int new_in, int new_out, int old_in, int old_out)
{
	if (new_in != old_in)
	{
		dup2(new_in, old_in);
		close(new_in);
	}
	if (new_out != old_out)
	{
		dup2(new_out, old_out);
		close(new_out);
	}
}

// Run a builtin cmd
void	handle_builtin(t_data *data, t_cmd *cmd, int child)
{
	const int	save_std[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
	int			err_code;

	dup_fds(cmd->in_fd, cmd->out_fd, STDIN_FILENO, STDOUT_FILENO);
	if (ft_strncmp(cmd->path, "echo", 5) == 0)
		err_code = run_echo(cmd->args);
	else if (ft_strncmp(cmd->path, "cd", 3) == 0)
		err_code = run_cd(data, cmd);
	else if (ft_strncmp(cmd->path, "pwd", 4) == 0)
		err_code = run_pwd(data);
	else if (ft_strncmp(cmd->path, "export", 7) == 0)
		err_code = run_export(data, cmd);
	else if (ft_strncmp(cmd->path, "unset", 6) == 0)
		err_code = run_unset(cmd->args, data);
	else if (ft_strncmp(cmd->path, "env", 4) == 0)
		err_code = run_env(data);
	else if (ft_strncmp(cmd->path, "exit", 5) == 0)
		err_code = run_exit(cmd, data, 0);
	dup_fds(save_std[0], save_std[1], STDIN_FILENO, STDOUT_FILENO);
	if (child)
		exit(err_code);
	data->err_code = err_code;
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

void	wait_for_children(t_data *data, int cmd_count)
{
	int	i;
	int	exit_status;

	i = 0;
	while (i <= cmd_count)
	{
		wait(&exit_status);
		i++;
	}
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

void	run_pipeline(t_data *data, t_cmd *cmd_list, int count_pipes)
{
	int			*pipefd;
	pid_t		pid;
	int			cmd_count;
	const int	save_std[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	pipefd = malloc(sizeof(int) * (count_pipes * 2));
	if (!pipefd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd_count = 0;
	create_pipes(pipefd, count_pipes);
	while (cmd_list)
	{
		if (cmd_list->in_fd != 0)
			dup2(cmd_list->in_fd, STDIN_FILENO);
		if (cmd_count > 0 && cmd_list->in_fd == 0)
			dup2(pipefd[cmd_count * 2 - 2], STDIN_FILENO);
		if (cmd_list->out_fd != 1)
			dup2(cmd_list->out_fd, STDOUT_FILENO);
		if (cmd_list->next)
			dup2(pipefd[cmd_count * 2 + 1], STDOUT_FILENO);
		pid = fork();
		signal(SIGINT, SIG_IGN);
		if (pid == 0)
		{
			signal(SIGINT, handle_signal);
			signal(SIGQUIT, SIG_DFL);
			close_all_pipes(pipefd, count_pipes);
			if (cmd_list->builtin)
				handle_builtin(data, cmd_list, 1);
			else if (cmd_list->path && execve(cmd_list->path, cmd_list->args,
					data->env_matrix) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else
		{
			dup2(save_std[1], STDOUT_FILENO);
			dup2(save_std[0], STDIN_FILENO);
		}
		cmd_list = cmd_list->next;
		cmd_count++;
	}
	close_all_pipes(pipefd, count_pipes);
	wait_for_children(data, cmd_count);
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	execute(t_data *data)
{
	int		count_pipes;
	t_cmd	*current;

	count_pipes = 0;
	data->cmd_list = group_cmd(data, data->token_list);
	// print_cmd(data->cmd_list);
	current = data->cmd_list;
	while (current && current->next)
	{
		count_pipes++;
		current = current->next;
	}
	if (!data->cmd_list)
		return ;
	if (!data->cmd_list->next && data->cmd_list->builtin)
		handle_builtin(data, data->cmd_list, 0);
	else
		run_pipeline(data, data->cmd_list, count_pipes);
}
