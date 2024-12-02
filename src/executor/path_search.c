/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lua <lua@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:49:05 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/30 11:45:51 by lua              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    ft_free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}


// Helper function to concatenate two strings with a '/' in between
static char *join_path(char *dir, char *cmd)
{
    char *full_path;
    printf("dir[%d]: %s\n", (int)ft_strlen(dir), dir);
    printf("cmd[%d]: %s\n", (int)ft_strlen(cmd), cmd);
    size_t len = strlen(dir) + strlen(cmd) + 2; // +2 for '/' and '\0'

    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    full_path = ft_strjoin (dir, "/");
    full_path = ft_strjoin_f(full_path, cmd, full_path, NULL);
    printf("%s\n", full_path);
    return (full_path);
}

char *search_absolute(t_data *data, char *cmd)
{
    (void)data;
    (void)cmd;
    return (NULL);
}

char *search_in_cwd(t_data *data, char *cmd)
{
    (void)data;
    (void)cmd;
    return (NULL);
}


char *search_in_env(t_data *data, char *cmd)
{
    char *path_env;
    char **paths;
    char *full_path;
    struct stat sb;
    int i;

    if (!cmd)
        return (NULL);
    path_env = get_env_value(data->env, "PATH");
    if (!path_env)
        return (NULL); // PATH not set
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (!full_path)
            break;
        // TODO: SIMPLIFY THIS CONDITION WITH ACCESS FUNCTION
        if (stat(full_path, &sb) == 0 && sb.st_mode & S_IXUSR)
        {
            ft_free_split(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    ft_free_split(paths);
    return (NULL); // Not found
}

int search_builtin(t_data *data, char *content){
    if()
}

// Handles the command path search and returns whether it was successful
// TODO: implementar las funciones de search_in_cmd and search_absolte
int	handle_command_path(t_data *data, t_cmd *cmd, char *content)
{
    if(search_builtin(data, content))
        return 1;
    cmd->path = search_in_cwd(data, content);
	if(!cmd->path)
        cmd->path = search_absolute(data, content);
    if(!cmd->path)
        cmd->path = search_in_env(data, content); 
    if (!cmd->path)
	{
        // FIX: deberia liberar no se porque hay un heap-use-after-free
		//free_cmd(cmd);
		return (0);
        // FIX: if this func returns 0 and it's not a builtin throw cmd not found
	}
	return (1);
}
