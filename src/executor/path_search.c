/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:49:05 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/19 01:46:57 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Helper function to concatenate two strings with a '/' in between
static char *join_path(char *dir, char *cmd)
{
    char *full_path;
    size_t len = strlen(dir) + strlen(cmd) + 2; // +2 for '/' and '\0'

    full_path = malloc(len);
    if (!full_path)
        return (NULL);
    printf(full_path, len, "%s/%s", dir, cmd);
    return (full_path);
}

char *search_absolute()
{
    return (NULL);
}

char *search_with_cwd()
{
    return (NULL);
}

char *search_in_env()
{
    return (NULL);
}

char *search_cmd_path(t_data *data, char *cmd)
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
        return (ft_strdup(cmd)); // PATH not set
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
    return (ft_strdup(cmd)); // Not found
}

// Handles the command path search and returns whether it was successful
int	handle_command_path(t_data *data, t_cmd *cmd, char *content)
{
    cmd->path = search_with_cwd(data, content);
	if(!cmd->path)
        cmd->path = search_absolute(content);
    if(!cmd->path)
        cmd->path = search_in_env(content); 
    if (!cmd->path)
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}