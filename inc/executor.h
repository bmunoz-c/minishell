/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:05:32 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/10 22:10:44 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_cmd {
    char *path;          // Path to the executable or built-in command
    char **args;         // Array of arguments for the command, including the command name
    char *input_file;    // File for input redirection, or NULL if not used
    char *output_file;   // File for output redirection, or NULL if not used
    //int append_output;   // Flag for >> redirection)
    int  is_builtin;       // Flag for builtins cmds
    struct s_cmd *next;
} t_cmd;


// Cmd list utils
t_cmd	*group_cmd(t_data *data, t_token *tk_list);