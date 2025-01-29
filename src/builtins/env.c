/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:36:21 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/29 14:23:44 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
- llamar env_as_matrix, ya aloca memoria.
- imprimir la matriz.
- liberar la matriz.
*/
int	run_env(t_data *data)
{
	char	**tmp;

	if (search_flags(data->cmd_list->args, "env"))
		return (SYNTAX_ERROR);
	tmp = data->env_matrix;
	if (!tmp)
		return (EXIT_SUCCESS);
	while (*tmp)
	{
		if (!ft_strchr(*tmp, '='))
		{
			tmp++;
			continue ;
		}
		ft_putendl_fd(*tmp, STDOUT_FILENO);
		tmp++;
	}
	ft_free_split(tmp);
	return (EXIT_SUCCESS);
}

// Cada vez que modifique env,
// tengo que actualizar el valor de la matriz en data.

/*
free env_matrix
llamar env_as_matrix
*/
