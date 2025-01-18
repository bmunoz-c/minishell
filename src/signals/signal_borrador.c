/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_borrador.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:55:01 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/18 12:59:41 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <signal.h>

void	handle_signal(int signal)
{
	g_sig_exit_status = signal;
	if (g_sig_exit_status == SIGINT)
	{
		printf("\n");
		exit(130);
	}
	else if (g_sig_exit_status == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
		exit(131);
	}
}

void	handle_signal_prompt(int signal)
{
	g_sig_exit_status = signal;
	if (g_sig_exit_status == SIGINT)
	{
		printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
