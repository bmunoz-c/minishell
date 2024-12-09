/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:29:28 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/09 22:55:29 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* If mode == 1, recibe SIGINT:
- Limpia la línea actual y pasa a una nueva línea.
- Redibuja el prompt para que el usuario pueda continuar escribiendo
sin interrupción.
- Actualiza la variable global g_sig para señalar que se ha recibido SIGINT. */

int init_signals(int mode)
{
    //Modo interactivo.
    if (mode == 1)
    {
        signal(SIGINT, ctrlc_handler);
        signal(SIGQUIT, SIG_IGN); // Ignorar SIGQUIT en modo interactivo
    }
    //Modo no interactivo.
    else if (mode == 2)
    {
        signal(SIGINT, exit_signal_handler);
        signal(SIGQUIT, exit_signal_handler);
    }
    //HERE_DOC HANDLER
    /* else if (mode == 3)
    {
        signal(SIGINT, heredoc_handler);
        signal(SIGQUIT, heredoc_handler);
    } */
    return (0);
}
//Ignorar señales.
/*signal() devuelve SIG_ERR si ocurre un error al intentar
configurar el manejador. En ese caso, se llama a exit(1).*/
void set_sig_ignore(int signum)
{
    if (signal(signum, SIG_IGN) == SIG_ERR)
        exit(1);
}

//Mantener el control de la línea de comandos tras Ctrl + C.
void	ctrlc_handler(int sig)
{
	(void)sig;
	{
        //El cursor pasa a una nueva línea en la terminal.
		ft_putstr_fd("\n", 1);
        //Borrar el contenido de la línea actual.
		rl_replace_line("", 1);
        //Registrar que se inicia una nueva línea.
		rl_on_new_line();
        //Redibujar el prompt en la nueva línea limpia.
		rl_redisplay();
        //Detecta que el usuario presionó CTRL + C
		sig_exit_status = 1;
	}
}
/* 
Interrumpe el proceso de heredoc:
- Detecta cuando el usuario presiona CTRL + C (que genera la señal SIGINT).
- Limpia la línea actual con rl_replace_line("", 1), la entrada del usuario no se queda visible en la terminal.

Restablece el prompt:
- rl_on_new_line() indica que comienza una nueva línea.
- rl_redisplay() redibuja el prompt limpio; se interrumpió el heredoc.

Notifica al programa del evento:
- sig_exit_status = 1 -> la señal SIGINT interrumpió el proceso.

Finaliza el heredoc:
- Llama a exit(1) para salir del proceso actual, cancelando efectivamente el heredoc.
*/
void	heredoc_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		sig_exit_status = 1;
		exit (1);
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

/* Se utiliza cuando el programa debe finalizar inmediatamente tras recibir SIGINT o SIGQUIT,
estableciendo códigos de salida (130 o 131) antes de salir. */
void exit_signal_handler(int sig)
{
    //CTRL + C
    if (sig == SIGINT)
    {
        sig_exit_status = 130;
        exit(130);
    }
    //CTRL + \.
    else if (sig == SIGQUIT)
    {
        sig_exit_status = 131;
        exit(130);
    }
}

