/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:04:56 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/10 22:05:27 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <unistd.h>

void	ft_putstring(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

int	check_option(char *arg, int *new_line)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	*new_line = 0;
	return (1);
}

int	run_echo(char **args)
{
	int	new_line;
	int	i;
	int	first_print;

	new_line = 1;
	if (!args[0])
	{
		ft_putchar_fd('\n', 1);
		return (0);
	}
	i = 0;
	while (args[i] && check_option(args[i], &new_line))
		i++;
	first_print = i;
	while (args[i])
	{
		if (i != first_print)
			ft_putchar_fd(' ', 1);
		ft_putstring(args[i++], 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (1);
}

/*int main(int argc, char **argv)
{
	ft_putstring("Main to check the echo built-in command\n", 1);
	ft_putstring("--------- Starting Execution ---------\n", 1);
	run_echo(&argv[1]);
	ft_putstring("---------- End of Execution ----------\n", 1);
}*/
