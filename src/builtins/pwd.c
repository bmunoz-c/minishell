/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:24:43 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/16 15:33:05 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
- Obtener el directorio actual de trabajo.
- Si no se puede obtener el directorio actual de trabajo,
	se obtiene el valor de la variable de entorno PWD.
*/
int	run_pwd(t_data *data)
{
	char	*pwd;

	if (search_flags(data->cmd_list->args, "pwd"))
		return (SYNTAX_ERROR);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		get_env_value(data->env, "PWD");
		if (!pwd)
			ft_putstr_fd(NOFILEDIR, 2);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
	return (EXIT_SUCCESS);
}
