/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:49:05 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/05 17:23:09 by ltrevin-         ###   ########.fr       */
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
char *join_path(char *dir, char *cmd)
{
    char *full_path;
    //printf("dir[%d]: %s\n", (int)ft_strlen(dir), dir);
    //printf("cmd[%d]: %s\n", (int)ft_strlen(cmd), cmd);
    size_t len = strlen(dir) + strlen(cmd) + 2; // +2 for '/' and '\0'

    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    ft_strlcpy(full_path, dir, len);
    ft_strlcat(full_path, "/", len);
    ft_strlcat(full_path, cmd, len);
    printf("%s\n", full_path);
    return (full_path);
}

char *search_absolute(t_data *data, char *cmd)
{
    (void)data;
    (void)cmd;
    return (NULL);
}

int verify_path(char *path)
{
    struct stat path_stat;

    // Check if the path exists
    if (access(path, F_OK) != 0) {
        //printf("access (file existence)");
        return 0;
    }
    // Use stat to check the type of file
    if (stat(path, &path_stat) != 0) {
        //printf("stat");
        return 0;
    }
    // Check if it is a directory
    if (S_ISDIR(path_stat.st_mode)) {
        //printf("The path '%s' is a directory and cannot be executed.\n", path);
        return 0;
    }
    // Check if the path is executable
    if (access(path, X_OK) == 0) {
        //printf("The path '%s' is executable and not a directory.\n", path);
        return 1;
    } else {
        //printf("access (execution check)");
        return 0;
    }

    return 0;
}

char *search_in_cwd(t_data *data, char *cmd)
{
    
    if (verify_path(cmd))
    {
        return (ft_strdup(cmd));
    }
    (void)data;
    (void)cmd;
    return (NULL);
}

char *search_in_env(t_data *data, char *cmd)
{
    char *path_env;
    char **paths;
    char *full_path;
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
        if (verify_path(full_path))
        {
            ft_free_split(paths);
            return (full_path);
        }
        free_ptr(full_path);
        i++;
    }
    ft_free_split(paths);
    return (NULL); // Not found
}

int search_builtin(char *content){
    if(ft_strncmp(content, "echo", 5) == 0 || ft_strncmp(content, "cd", 3) == 0 
    || ft_strncmp(content, "pwd", 4) == 0 || ft_strncmp(content, "export", 7) == 0 
    || ft_strncmp(content, "unset", 6) == 0 || ft_strncmp(content, "env", 4) == 0 
    || ft_strncmp(content, "exit", 5) == 0)
        return 1;
    else
        return 0;
}

// Handles the command path search and returns whether it was successful
// TODO: implementar las funciones de search_in_cmd and search_absolte
int	handle_command_path(t_data *data, t_cmd *cmd, char *content)
{
    if(search_builtin(content))
        return 1;
    cmd->path = search_in_cwd(data, content);
	if(!cmd->path)
        cmd->path = search_absolute(data, content);
    if(!cmd->path)
        cmd->path = search_in_env(data, content); 
    if (!cmd->path)
		return (0);
    // FIX: if this func returns 0 and it's not a builtin throw cmd not found
	return (1);
}
