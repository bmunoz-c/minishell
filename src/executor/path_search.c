/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:49:05 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/12/09 21:18:55 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Helper function to concatenate two strings with a '/' in between
char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	size_t	len;

	len = strlen(dir) + strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

int	verify_path(char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
		return (NOT_FOUND);
	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (IS_DIR);
	if (access(path, X_OK) == 0)
		return (IS_F_EXEC);
	return (0);
}

char	**get_paths_from_env(t_data *data)
{
	char	**paths;
	char	*path_env;

	path_env = get_env_value(data->env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*search_in_env(t_data *data, char *cmd)
{
	char	**paths;
	char	*full_path;
	int		i;

	paths = get_paths_from_env(data);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i++], cmd);
		if (!full_path)
			break ;
		if (verify_path(full_path) == IS_F_EXEC)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free_ptr(full_path);
	}
	ft_free_split(paths);
	return (NULL);
}

// Handles the command path search and returns whether it was successful
// TODO: if this func returns 0 and it's not a builtin throw cmd not found
int	handle_command_path(t_data *data, t_cmd *cmd, char *content)
{
	if (ft_strncmp(content, "echo", 5) == 0
		||ft_strncmp(content, "cd", 3) == 0
		|| ft_strncmp(content, "pwd", 4) == 0
		|| ft_strncmp(content, "export", 7) == 0
		|| ft_strncmp(content, "unset", 6) == 0
		|| ft_strncmp(content, "env", 4) == 0
		|| ft_strncmp(content, "exit", 5) == 0)
	{
		cmd->builtin = 1;
		cmd->path = ft_strdup(content);
		return (1);
	}
	if (verify_path(content) == IS_F_EXEC)
		cmd->path = ft_strdup(content);
	if (!cmd->path)
		cmd->path = search_in_env(data, content);
	if (!cmd->path)
		return (0);
	return (1);
}
