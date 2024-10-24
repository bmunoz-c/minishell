/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mng.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:52:46 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/17 19:34:55 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_error(t_data *data, char *msg)
{
	data->err_code = SYNTAX_ERROR;
	data->err_msg = ft_strjoin("syntax error", msg);
	return (1);
}

void	metachars_error(t_data *data, char *metachars)
{
	(void)metachars;
	data->err_code = SYNTAX_ERROR;
}
