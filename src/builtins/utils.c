/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:05:55 by ltrevin-          #+#    #+#             */
/*   Updated: 2025/01/16 17:50:52 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Receives a string that has already passed
	all the necessary checks, and converts it from char
	to long long int.
*/
long long	ft_atoll(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

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
