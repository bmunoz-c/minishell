/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:05:55 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/13 22:42:31 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_flag(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[1] == '\0')
		return (0);
	while (str[i] && ft_isalpha(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

// TODO Add data to add the errror code
int	search_flags(char **cmd, char *name)
{
	int	i;

	if (!cmd || !cmd[0])
		return (0);
	i = 1;
	while (cmd[i])
	{
		if (is_flag(cmd[i]))
		{
			printf(FLAG_FOUND, PROGRAM_NAME, name, *(cmd[i]), *(cmd[i] + 1));
			return (2);
		}
		i++;
	}
	return (0);
}

int	ft_error(const char *cmd_name, const char *msg, int err_code)
{
	printf("%s: %s\n", cmd_name, msg);
	return (err_code);
}
