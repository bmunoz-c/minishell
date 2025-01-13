/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/13 20:27:06 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_fds(int new_in, int new_out, int old_in, int old_out)
{
	if (new_in != old_in)
	{
		dup2(new_in, old_in);
		//close(new_in);
	}
	if (new_out != old_out)
	{
		dup2(new_out, old_out);
		//close(new_out);
	}
}

// Run a builtin cmd
void	handle_builtin(t_data *data, t_cmd *cmd, int child)
{
	const int	save_std[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};
    int err_code;

	dup_fds(cmd->in_fd, cmd->out_fd, STDIN_FILENO, STDOUT_FILENO);
	if (ft_strncmp(cmd->path, "echo", 5) == 0)
		err_code = run_echo(cmd->args);
	else if (ft_strncmp(cmd->path, "cd", 3) == 0)
        err_code = run_cd(data, data->env, cmd);
	else if (ft_strncmp(cmd->path, "pwd", 4) == 0)
		err_code = run_pwd(data);
	else if (ft_strncmp(cmd->path, "export", 7) == 0)
        err_code = run_export(data, cmd);
	else if (ft_strncmp(cmd->path, "unset", 6) == 0)
        err_code = run_unset(cmd->args, data);
	else if (ft_strncmp(cmd->path, "env", 4) == 0)
		err_code = run_env(data);
	else if (ft_strncmp(cmd->path, "exit", 5) == 0)
	{
		run_exit(cmd, data, 0);
		return ;
	}
	dup_fds(save_std[0], save_std[1], STDIN_FILENO, STDOUT_FILENO);
	if(child)
		exit(EXIT_SUCCESS);
    data->err_code = err_code;
}

void run_pipeline(t_data *data, t_cmd *cmd_list)
{
    int pipefd[2];
    pid_t pid;
    int fd_in = STDIN_FILENO; // Input for the first command
    int last_pid = -1; // To keep track of the last process ID
	const int	save_std[2] = {dup(STDIN_FILENO), dup(STDOUT_FILENO)};

    while (cmd_list)
    {
        if (cmd_list->next)
        {
            if (pipe(pipefd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            pipefd[0] = STDIN_FILENO;
            if (cmd_list->out_fd != STDOUT_FILENO)
                pipefd[1] = cmd_list->out_fd;
            else
                pipefd[1] = STDOUT_FILENO;
        }

        pid = fork();
        if (pid == 0)
        {
            // Child 
            dup_fds(fd_in, pipefd[1], STDIN_FILENO, STDOUT_FILENO);
            if (cmd_list->builtin)
                handle_builtin(data, cmd_list, 1);
            else if (cmd_list->path && execve(cmd_list->path, cmd_list->args, data->env_matrix) == -1)
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
            // parent
            last_pid = pid; 
            close(pipefd[1]);
            fd_in = pipefd[0]; 
        }

        cmd_list = cmd_list->next;
    }

    waitpid(last_pid, NULL, 0);
	dup_fds(save_std[0], save_std[1], STDIN_FILENO, STDOUT_FILENO);
}

void	execute(t_data *data)
{
	data->cmd_list = group_cmd(data, data->token_list);
	print_cmd(data->cmd_list);
	
	if (!data->cmd_list)
		return ;
	if (!data->cmd_list->next && data->cmd_list->builtin)
		handle_builtin(data, data->cmd_list, 0);
	else
		run_pipeline(data, data->cmd_list);
}
