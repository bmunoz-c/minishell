/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:29:28 by bmunoz-c          #+#    #+#             */
/*   Updated: 2025/01/17 17:49:07 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
- mode == 1, recibe SIGINT: (Modo interactivo)
- mode == 2, recibe SIGINT y SIGQUIT: (Modo no interactivo)
- mode == 3, recibe SIGINT y SIGQUIT: (Modo heredoc)
*/
int	init_signals(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, ctrlc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == 2)
	{
		signal(SIGINT, exit_signal_handler);
		signal(SIGQUIT, exit_signal_handler);
	}
	else if (mode == 3)
	{
		signal(SIGINT, heredoc_handler);
		signal(SIGQUIT, heredoc_handler);
	}
	return (0);
}

// Ignorar señales.
/*signal() devuelve SIG_ERR si ocurre un error al intentar
configurar el manejador. En ese caso, se llama a exit(1).*/
void	set_sig_ignore(int signum)
{
	if (signal(signum, SIG_IGN) == SIG_ERR)
		exit(1);
}

/* 
Mantener el control de la línea de comandos tras Ctrl + C.
- El cursor pasa a una nueva línea en la terminal.
- Borrar el contenido de la línea actual.
- Registrar que se inicia una nueva línea.
- Redibujar el prompt en la nueva línea limpia.
- Detecta que el usuario presionó CTRL + C

*/
void	ctrlc_handler(int sig)
{
	(void)sig;
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig_exit_status = 1;
	}
}

/*
Interrumpe el proceso de heredoc:

Notifica al programa del evento:
- sig_exit_status = 1 -> la señal SIGINT interrumpió el proceso.

Finaliza el heredoc:
- Llama a exit(1) para salir del proceso actual,
	cancelando efectivamente el heredoc.
*/
void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		g_sig_exit_status = 1;
		exit(1);
	}
}

/*
La función maneja dos señales específicas:
- SIGINT (Ctrl + C): Establece el estado de salida en 130
y termina el proceso con el mismo código.
- SIGQUIT (Ctrl + ): Establece el estado de salida en 131
pero también termina el proceso con el código 130.

- exit_code = 128 + signal.
- SIGINT: = 2
- SIGQUIT: = 3
*/
void	exit_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_exit_status = 130;
		printf("\n");
		exit(130);
	}
	else if (sig == SIGQUIT)
	{
		g_sig_exit_status = 131;
		printf("Quit (core dumped)\n");
		exit(131);
	}
}
