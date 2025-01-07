/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:36:21 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/07 17:14:29 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
- llamar env_as_matrix, ya aloca memoria.
- imprimir la matriz.
- liberar la matriz.
*/
void    run_env(t_data *data)
{
    char    **tmp;

    if(search_flags(data->cmd_list->args, "env"))
        return ;
    tmp = data->env_matrix;
    while (*tmp)
    {
        ft_putendl_fd(*tmp, STDOUT_FILENO);
        tmp++;
    }
}

//Cada vez que modifique env,
//tengo que actualizar el valor de la matriz en data.

/* 
free env_matrix
llamar env_as_matrix 
*/