/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 21:19:52 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/24 20:26:25 by jsebasti         ###   ########.fr       */
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

///////////// INIT STRUCTS
void		init_data(t_data *data);
void		init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last);

///////////// ENVIROMENT
void		copy_env(char **org_env, t_data *data);
void		free_env(t_env *env);
char		*get_env_value(t_env *env, char *key);
t_env		*get_env(t_env *env, char *key);
t_env		*new_env(char *key, char *value);
void		add_env(t_env **env_list, t_env *new_env);
void		change_env_value(char *key, char *value, t_env **env_lst);

//////////// INIT STRUCTS
void		init_cmd_data(t_cmd *cmd, t_token *tk_first, t_token *tk_last);
void		init_data(t_data *data);

//////////// FREE utils
// void		*free_ptr(void **ptr);
void		*free_ptr(void *ptr);
void		*free_cmd(t_cmd *cmd);
void		free_cmds(t_cmd *cmd_list);
void		free_env(t_env *env);
void		free_tokens(t_token *token_list);
void		free_token(t_token *token);
void		free_data(t_data *data, int env_flag);

//////////// SIGNALS
/* int			init_signals(int mode);
void		set_sig_ignore(int signum);
void		ctrlc_handler(int sig);
void	exit_signal_handler(int sig); */

void		heredoc_handler(int signal);
void		handle_signal(int signal);
void		handle_signal_prompt(int signal);

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

#endif

////////// BUG: Print utils, delete before submit
void		print_env(t_env *env);
void		print_cmd(t_cmd *cmd);

////////// HEREDOC

void	exec_here(t_data *data, const char *del);
void	print_here(t_data *data, const char *del, int fd);

