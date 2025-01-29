/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_borrador.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:55:01 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/29 12:31:10 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

void	handle_signal(int sig)
{
	write(1, "a", 1);
	if (sig == SIGINT)
		write(1, "\n", 1);
	else if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
}

void	handle_signal_prompt(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

