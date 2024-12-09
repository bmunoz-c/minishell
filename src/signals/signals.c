/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 20:29:28 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/09 19:53:59 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
- Inicializa una estructura sigaction.
- Configura los flags y la máscara de señales.
- Selecciona el manejador de señales según mode.
- Aplica la configuración para SIGINT y SIGQUIT.
- Devuelve 0. */

int init_signals(int mode)
{
    struct sigaction signal;

    signals.sa_flags = SA_RESTART|SA_SIGINFO;
}

/*
- exit_code = 128 + signal.
- SIGINT: = 2
- SIGQUIT: = 3
*/
void exit_signal_handler(int sig, siginfo_t *info, void *ucontext)
{
    (void)info;
    (void)ucontext;
    //CTRL + C
    if (sig == SIGINT)
    {
        g_sig = 130;
        exit(130);
    }
    //CTRL + \.
    else if (sig == SIGQUIT)
    {
        g_sig = 131;
        exit(131);
    }
    return (0);
}