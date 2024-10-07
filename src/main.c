#include <stdio.h>
int			main(int ac, char **av, char **env)
{
	ac = 0;
	av[0] = "hola\n";
	printf("Holaa soy un minishell que va a quedar xulisimo\n");
	printf("%s\n", env[0]);
}
