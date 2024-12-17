/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:50:26 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/17 13:49:35 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// Run a builtin cmd
void handle_builtin(t_data *data, t_cmd *cmd) 
{
	(void)data;
	(void)cmd;
	if (ft_strncmp(cmd->path, "echo", 5) == 0)
		run_echo(cmd->args);
	// else if (ft_strncmp(cmd->path, "cd", 3) == 0)
	else if (ft_strncmp(cmd->path, "pwd", 4) == 0)
        run_pwd(data);
	// else if (ft_strncmp(cmd->path, "export", 7) == 0)
	// else if (ft_strncmp(cmd->path, "unset", 6) == 0)
	else if (ft_strncmp(cmd->path, "env", 4) == 0)
        run_env(data);
	else if (ft_strncmp(cmd->path, "exit", 5) == 0)
    {
        run_exit(cmd, data, 0);
        return ;
    }
    run_exit(NULL, data, 1);
}

void dup_fds(int in, int out)
{
    if (in != STDIN_FILENO)
    {
        dup2(in, STDIN_FILENO);
        close(in);
    }
    if (out != STDOUT_FILENO)
    {
        dup2(out, STDOUT_FILENO);
        close(out);
    }
}

// Case when it's only one command in prompt
void run_single(t_data *data, t_cmd *cmd)
{
    pid_t pid;
    int status;

    if(cmd->builtin && ft_strncmp(cmd->path, "exit", 5) == 0)
    {
        handle_builtin(data, cmd);
        return ;
    }
    pid = fork();
    if (pid == 0)
    {
        dup_fds(cmd->in_fd, cmd->out_fd);
        if (cmd->builtin)
            handle_builtin(data, cmd);
        else if (execve(cmd->path, cmd->args, data->env_matrix) == -1)
            run_exit(NULL, data, 1);
    }
    else if (pid < 0)
        run_exit(NULL, data, 1);
    else 
        waitpid(pid, &status, 0);
}

// Case when there are multiple commnads in prompt
void run_pipeline(t_data *data, t_cmd *cmd)
{
	(void)data;
	(void)cmd;	
}




void execute(t_data *data)
{
    data->cmd_list = group_cmd(data, data->token_list);
	//print_cmd(data->cmd_list);
	if(!data->cmd_list)
		return ;
	if(!data->cmd_list->next)
		run_single(data, data->cmd_list);
    else
		run_pipeline(data, data->cmd_list);
}
