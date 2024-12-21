/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:51 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/12 16:23:08 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <minishell.h>

void set_error(t_data *data, const char *msg, int err_code, int cd_print)
{
    free(data->err_msg);
    if (cd_print && msg)
        data->err_msg = ft_strjoin("cd: ", msg);
    else
        data->err_msg = ft_strdup(msg);
    data->err_code = err_code;
}

int cd_access(t_data *data, char *path)
{
    struct stat st;

    // Validar que el puntero path no sea NULL
    if (!path)
        return (set_error(data, PATH_NULL, 1, 0), 1);
    // Obtener información del archivo o directorio
    if (lstat(path, &st) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (set_error(data, INV_PATH, 126, 0), 1);
    }
    // Comprobar existencia
    if (access(path, F_OK) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (set_error(data, NOFILEDIR, 127, 0), 1);
    }
    // Comprobar si es un directorio
    if (!S_ISDIR(st.st_mode))
        return (set_error(data, NOTDIR, 126, 0), 1);
    // Comprobar permisos de ejecución
    if (access(path, X_OK) == -1)
        return (set_error(data, PERM_DENIED, 126, 0), 1);
    // Todo está bien
    return (set_error(data, NULL, 0, 1), 0);
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
//TODO: Implementar la función cd_path
int cd_path(t_data *data, t_cmd *cmd)
{
    char    *path;
    char    *oldpwd;

    path = cmd->args[1];
    oldpwd = ft_getcwd();
    if (oldpwd == NULL)
        return (1);
    
}
//TODO: Implementar la función cd_home
int run_cd(t_data *data, t_env *env, t_cmd *cmd)
{
    char    *home;
    char    *oldpwd;

    home = get_env_value(env, "HOME");
    oldpwd = ft_getcwd();
    if (oldpwd == NULL)
        return (1);
    
   
}
