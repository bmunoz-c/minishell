#include <minishell.h>
#include <signal.h>

/* 
- Inicializa una estructura sigaction.
- Configura los flags y la máscara de señales.
- Selecciona el manejador de señales según mode.
- Aplica la configuración para SIGINT y SIGQUIT.
- Devuelve 0. */

/* 
- sa_flags: Opciones para configurar el comportamiento del manejador.
- sa_mask: Especifica señales que deben bloquearse durante la ejecución del manejador.
- sa_sigaction: Puntero a la función que manejará la señal. 
     void (*sa_sigaction)(int, siginfo_t *, void *);

*/

/* If mode == 1, recibe SIGINT:
- Limpia la línea actual y pasa a una nueva línea.
- Redibuja el prompt para que el usuario pueda continuar escribiendo
sin interrupción.
- Actualiza la variable global g_sig para señalar que se ha recibido SIGINT. */

int init_signals(int mode)
{
    struct sigaction signal;

    signal.sa_flags = SA_RESTART | SA_SIGINFO;
    sigemptyset(&signal.sa_mask);
    if (mode == 1)
        signal(SIGINT, ctrlc_handler);
    else if (mode == 2)
        signal.sa_sigaction = &exit_signal_handler;
    //HERE_DOC HANDLER
    /* else if (mode == 3)
    {
        
    } */
    sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
    return (0);
}

//Mantener el control de la línea de comandos tras Ctrl + C.

void	ctrlc_handler(int sig, siginfo_t *data, void *non_used_data)
{
	(void) data;
	(void) non_used_data;
	if (sig == SIGINT)
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
void exit_signal_handler(int sig, siginfo_t *data, void *unused_data)
{
    (void)data;
    (void)unused_data;
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
    return (0);
}

