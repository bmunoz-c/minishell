#include <minishell.h>

void set_error(t_data *data, const char *msg, int err_code)
{
    free(data->err_msg);
    data->err_msg = ft_strdup(msg);
    data->err_code = err_code;
}

int cd_access(t_data *data, char *path)
{
    struct stat st;

    // Validar que el puntero path no sea NULL
    if (!path)
        return (set_error(data, PATH_NULL, 1), 1);
    // Obtener información del archivo o directorio
    if (lstat(path, &st) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (set_error(data, INV_PATH, 126), 1);
    }
    // Comprobar existencia
    if (access(path, F_OK) == -1)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        perror(path);
        return (set_error(data, NOFILEDIR, 127), 1);
    }
    // Comprobar si es un directorio
    if (!S_ISDIR(st.st_mode))
        return (set_error(data, NOTDIR, 126), 1);
    // Comprobar permisos de ejecución
    if (access(path, X_OK) == -1)
        return (set_error(data, PERM_DENIED, 126), 1);
    return (set_error(data, NULL, 0), 0);
    // Todo está bien
}
