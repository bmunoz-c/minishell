#include <stdio.h>
#include <unistd.h>


void ft_putchar_fd(char ch, int fd)
{
	write(1, &ch, fd);
}

void ft_putstring(char *s, int fd)
{
	int i;

	i = 0;
	while(s[i])
		ft_putchar_fd(s[i++], fd);
}


int check_option(char *arg, int *new_line)
{
	int i = 1;
	int n = 0;
	if(arg[0] != '-')
		return(0);
	while(arg[i])
	{
		if(arg[i] == 'n')
			n = 1;
		if(arg[i] != 'n')
			return(0);
		i++;
	}
	*new_line = 0;
	return(1);
}

int run_echo(char **args)
{
	int new_line = 1;
	int i;
	int first_print;
	// when no args
	if(!args[0])
	{
		ft_putchar_fd('\n', 1);
		return(0);
	}
	i = 0;
	// iter all args & ommit all valid flags
	while(args[i] && check_option(args[i], &new_line))
		i++;
	//printf("Primer arg = %d", i);
	first_print = i;
 	// print rest of the string
	while(args[i])
	{
		if(i != first_print)
			ft_putchar_fd(' ', 1);
		ft_putstring(args[i++], 1);
	}
	if(new_line)
		ft_putchar_fd('\n',1);
	return(1);
}

/*int main(int argc, char **argv)
{
	ft_putstring("Main to check the echo built-in command\n", 1);
	ft_putstring("--------- Starting Execution ---------\n", 1);
	run_echo(&argv[1]);
	ft_putstring("---------- End of Execution ----------\n", 1);
}*/
