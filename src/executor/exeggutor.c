/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeggutor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/29 19:28:51 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	exec_child(int *pipefd, t_data *data, t_cmd *cmd_list)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_DFL);
	close_all_pipes(pipefd, data->count_pipes);
	if (cmd_list->builtin)
		handle_builtin(data, cmd_list, 1);
	else if (cmd_list->path && execve(cmd_list->path, cmd_list->args,
			data->env_matrix) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

void	create_childs(int *pipefd, t_data *data, t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		exec_child(pipefd, data, cmd);
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return ;
}

void	run_pipeline(t_data *data, t_cmd *cmd_list)
{
	int			*pipefd;
	int			cmd_count;
	const int	save_std[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

	pipefd = malloc(sizeof(int) * (data->count_pipes * 2));
	if (!pipefd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd_count = 0;
	create_pipes(pipefd, data->count_pipes);
	while (cmd_list)
	{
		asign_in_out(pipefd, cmd_list, cmd_count);
		create_childs(pipefd, data, cmd_list);
		dup_fds(save_std[0], save_std[1], STDIN_FILENO, STDOUT_FILENO);
		cmd_list = cmd_list->next;
		cmd_count++;
	}
	close_all_pipes(pipefd, data->count_pipes);
	wait_for_children(data, cmd_count);
}

void	execute(t_data *data)
{
	t_cmd	*current;

	data->count_pipes = 0;
	data->cmd_list = group_cmd(data, data->token_list);
	current = data->cmd_list;
	while (current && current->next)
	{
		data->count_pipes++;
		current = current->next;
	}
	if (!data->cmd_list)
		return ;
	if (!data->cmd_list->next && data->cmd_list->builtin)
		handle_builtin(data, data->cmd_list, 0);
	else
		run_pipeline(data, data->cmd_list);
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
}
