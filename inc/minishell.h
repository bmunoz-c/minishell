/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:19:52 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/31 08:15:35 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <error.h>
# include <fcntl.h>
# include <libft/libft.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <tokenizer.h>

extern int	g_sig_exit_status;
void		copy_env(char **org_env, t_data *data);

// COLOR MACROS
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define HEREDOC_NAME "/tmp/dancingshell_heredoc"

# define PROMPT "\033[0;35mdancingShell🩰🦦 \033[0;34m> \033[0m"

# define EXIT_SUCCES 0
# define EXIT_FAILURE 1

///////////// INIT STRUCTS
void		init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last);
void		init_data(t_data *data);

///////////// ENVIROMENT
void		copy_env(char **org_env, t_data *data);
void		free_env(t_env *env);
char		*get_env_value(t_env *env, char *key);
t_env		*get_env(t_env *env, char *key);
t_env		*new_env(char *key, char *value);
void		add_env(t_env **env_list, t_env *new_env);
void		change_env_value(char *key, char *value, t_env **env_lst);

//////////// FREE utils
// void		*free_ptr(void **ptr);
void		*free_ptr(void *ptr);
void		*free_cmd(t_cmd *cmd);
void		free_cmds(t_cmd *cmd_list);
void		free_env(t_env *env);
void		free_tokens(t_token *token_list);
void		free_token(t_token *token);
void		free_data(t_data *data, int env_flag);
int			free_on_error(t_cmd *cmd, int i_args);

//////////// SIGNALS
void		heredoc_handler(int sig);
void		handle_signal(int sig);
void		handle_signal_prompt(int sig);

void		ft_free_split(char **split);

char		**env_as_matrix(t_env *env, char **arr);

///////////// BUILTINS
int			run_echo(char **args);
int			run_pwd(t_data *data);
int			run_exit(t_cmd *cmd, t_data *data, int is_child);
int			run_env(t_data *data);
int			run_unset(char **cmd, t_data *data);
int			run_export(t_data *data, t_cmd *cmd);

///////////// EXPORT_UTILS
int			valid_varname(char *str);
char		*export_var(t_env *env, char *arg, t_data *data, char *key);
char		*rm_plus(char *str);
void		print_export(t_env *env);
char		*get_key(char *str);
void		update_environment(t_data *data, const char *arg, char *key,
				int export_code);
int			run_cd(t_data *data, t_cmd *cmd);

//////////// BUILTINS UTILS
int			search_flags(char **cmd, char *cmd_name);
int			ft_error(const char *cmd_name, const char *msg, int err_code);
long long	ft_atoll(const char *str);

/////////// EXECUTION
t_cmd		*group_cmd(t_data *data, t_token *tk_list);
void		execute(t_data *data);
int			handle_command_path(t_data *data, t_cmd *cmd, char *content,
				t_token *tk);

int			search_redirs(t_cmd *cmd, t_token *tk_list, t_token *tk_last,
				int in_pathhand);
int			save_args(t_cmd *cmd, int *i_args, char *content);
int			check_relative_cmd(t_cmd *cmd, t_data *data, char *content);
int			check_builtin(t_cmd *cmd, char *content, int flag);
char		*search_in_env(t_data *data, char *cmd);
void		create_cmd(t_data *data, t_token *tk_list, t_token *tk_last,
				t_cmd **cmd_list);
void		add_cmd(t_cmd **cmd_list, t_cmd *cmd);
t_cmd		*build_cmd(t_data *data, t_token *tk_list, t_token *tk_last);

////////// HEREDOC

void		exec_here(t_token *delimiter);
void		print_here(const char *del, int fd);
int			check_heredoc(t_token *tk_list, t_data *data);

/////////	PIPES

void		dup_fds(int new_in, int new_out, int old_in, int old_out);
void		close_all_pipes(int *pipefd, int count_pipes);
void		wait_for_children(t_data *data, int cmd_count);
void		create_pipes(int *pipefd, int count_pipes);
void		asign_in_out(int *pipefd, t_cmd *cmd_list, int cmd_count);
int			open_file(int *fd, char *path, int flags, int mode);
int			input_tokens(t_cmd *cmd, t_token *tk_list, int in_pathhand);
int			output_tokens(t_cmd *cmd, t_token *tk_list);

#endif
