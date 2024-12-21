/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:36:21 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/17 13:43:47 by bmunoz-c         ###   ########.fr       */
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