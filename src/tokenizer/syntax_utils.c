/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:17:53 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/15 17:21:33 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenizer.h"
#include "../../inc/metachars.h"
#include "../../inc/error.h"
#include "../../inc/libft/libft.h"

//is <>, <<>>
int	is_redirection(char *line, int index)
{
	return (line[index] == INPUT_RD[0]
		|| line[index] == OUTPUT_RD[0]
		|| (line[index] == INPUT_RD[0] && line[index + 1] == INPUT_RD[0])
		|| (line[index] == OUTPUT_RD[0] && line[index + 1] == OUTPUT_RD[0]));
}

/*
void	metachars_error(t_data *data, char *metachars)
{
	(void)metachars;
	data->err_code = SYNTAX_ERROR;
}*/

//if |, <>, <<>>
int	check_metachar(t_data *data, char *line, int i)
{
	if (line[i] == PIPE[0])
		return (metachars_error(data, PIPE), 0);
	else if (line[i] == INPUT_RD[0] && line[i + 1] == INPUT_RD[0])
		return (metachars_error(data, HERE_DOC_RD), 0);
	else if (line[i] == OUTPUT_RD[0] && line[i + 1] == OUTPUT_RD[0])
		return (metachars_error(data, APPEND_RD), 0);
	else if (line[i] == INPUT_RD[0])
		return (metachars_error(data, INPUT_RD), 0);
	else if (line[i] == OUTPUT_RD[0])
		return (metachars_error(data, OUTPUT_RD), 0);
	return (1);
}
