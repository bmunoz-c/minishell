/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:20:01 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/27 13:22:15 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_err_many_args_exit(t_data *data)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putendl_fd(" exit: too many arguments", STDERR_FILENO);
	data->err_code = 1;
	return (data->err_code);
}

int	print_err_num_arg(t_data *data, char *cmd)
{
	ft_putstr_fd(PROGRAM_NAME, STDERR_FILENO);
	ft_putstr_fd(" exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	data->err_code = 2;
	return (data->err_code);
}

//Returns 1 if the string is a valid number and 0 if it is not.
int	check_llong(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
    Receives a str and checks that it is,
    converted to a number, within the long long int limits
    (LLONG MIN - LLONG MAX).
*/
char    check_ll_max_min(const char *str)
{
    int     i; 
    int    len;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    len = ft_strlen(str);
    if (len > 19)
        return (0);
    if (len < 19)
        return (1);
    if (str[0] == '-')
    {
        if (ft_strncmp("9223372036854775808", &(str[i]), len) < 0)
            return (0);
    }
    else
    {
        if (ft_strncmp("9223372036854775807", &(str[i]), len) < 0)
            return (0);
    }
    return (1);    
}

/* 
    Receives a string that has already passed 
    all the necessary checks, and converts it from char 
    to long long int.
*/
long long   ft_atoll(const char *str)
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

/*
-Finalizar la ejecución de la minishell.
-Liberar recursos asignados.
-Manejar avs de entrada para establecer un buen código de salida.
-Validar errores específicos, como avs no num o demasiados avs.
*/
int	run_exit(t_cmd *cmd, t_data *data, int is_child)
{
	if (isatty(STDIN_FILENO) && !is_child)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (cmd && cmd->args && cmd->args[1])
	{

		if (check_llong(cmd->args[1]) && check_ll_max_min(cmd->args[1]))
			data->err_code = ft_atoll(cmd->args[1]);
		else
		{
			print_err_num_arg(data, cmd->args[1]);
            exit(data->err_code);
		}
	}
	if (cmd && cmd->nargs > 2)
		return (print_err_many_args_exit(data));
	if(!cmd)
		data->err_code = 1;
	exit(data->err_code);
	return (EXIT_SUCCESS);
}
