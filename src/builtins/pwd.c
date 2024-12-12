/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:24:43 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/12 18:16:30 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    pwd(t_data *data)
{
    char    *pwd;
    
    //Ovtener el directorio actual de trabajo.
    pwd = getcwd(NULL, 0);
    //Si no se puede obtener el directorio actual de trabajo,
    if (!pwd)
    {
        //Se obtiene el valor de la variable de entorno PWD.
        get_env_value(data->env, "PWD");
        if (!pwd)
            ft_putstr_fd(NOFILEDIR, 2);
    }
    ft_putstr_fd(pwd, 1);
    ft_putstr_fd("\n", 1);
    free(pwd);
}