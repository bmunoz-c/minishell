/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:51 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/13 22:43:48 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd_access(char *path)
{
	struct stat	st;

	// Validar que el puntero path no sea NULL
	if (!path)
		return (ft_error("cd", PATH_NULL, 1));
	// Comprobar existencia
	if (access(path, F_OK) == -1)
		return (ft_error("cd", NOFILEDIR, 1));
	// Comprobar si es un directorio
	if (stat(path, &st) != 0)
		return (ft_error("cd", STAT_ERR, 1));
	if (!S_ISDIR(st.st_mode))
		return (ft_error("cd", NOTDIR, 1));
	// Comprobar permisos de ejecución
	if (access(path, X_OK) == -1)
		return (ft_error("cd", PERM_DENIED, 1));
	// Todo está bien
	return (0);
}

// Obtener el directorio de trabajo (gwd) actual
// como una cadena de caracteres dinámica.
char	*ft_getcwd(void)
{
	char	*res;

	res = getcwd(NULL, 0);
	if (!res)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd(NOFILEDIR, 2);
		return (NULL);
	}
	return (res);
}

// TODO: Implementar la función cd_path
int	cd_path(t_env **env_lst, t_cmd *cmd)
{
	char	*path;
	char	*oldpwd;

	path = cmd->args[1];
	oldpwd = ft_getcwd();
	if (oldpwd == NULL)
		return (1);
	change_env_value("OLDPWD", oldpwd, env_lst);
	if (get_env_value(*env_lst, "OLDPWD"))
		change_env_value("OLDPWD", oldpwd, env_lst);
	free(oldpwd);
	chdir(path);
	oldpwd = ft_getcwd();
	change_env_value("PWD", oldpwd, env_lst);
	free(oldpwd);
	return (0);
}

// TODO: Implementar la función cd_home
int	run_cd(t_data *data, t_cmd *cmd)
{
	char	*oldpwd;
	int		ret;

	if (search_flags(cmd->args, "cd"))
		return (2);
	if (cmd->nargs != 2)
		return (ft_error("cd", WRONG_ARG, 1));
	ret = cd_access(cmd->args[1]);
	if (ret != 0)
		return (ret);
	oldpwd = ft_getcwd();
	if (oldpwd == NULL)
		return (1);
	free(oldpwd);
	if (cd_access(cmd->args[1]))
		return (1);
	if (cd_path(&data->env, cmd))
		return (1);
	data->env_matrix = env_as_matrix(data->env, data->env_matrix);
	return (0);
}
