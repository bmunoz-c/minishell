/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:04:14 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/18 13:55:04 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* 
This function receives the variable to be exported and checks
if it already exists in the data->env list.  

Ret:    -1 if no matches are found.
        || returns the position in the array in which it is found.
*/
int	check_if_exist(char *var, t_data *data)
{
    int i;
    int var_len;
    int env_key_len;
    char *equal_pos_env;
    char *equal_pos_var;
    
    i = 0;
    equal_pos_var = ft_strchr(var, '=');
    if (equal_pos_var)
        var_len = equal_pos_var - var;
    else
        var_len = ft_strlen(var);
    while (data->env && &data->env[i])
    {
        equal_pos_env = ft_strchr(&data->env[i], '=');
        if (equal_pos_env)
            env_key_len = ft_strchr(&data->env[i], '=') - &data->env[i];
        else
            env_key_len = ft_strlen(&data->env[i]);
        if (var_len == env_key_len && ft_strncmp(&data->env[i], var, env_key_len) == 0)
            return (1);
        i++;
    }
    return (-1);
}

void	check_cmd(t_cmd *cmd, int *i, t_data *data)
{
	if (cmd->args[1] == '\0')
	{
		printf("%s: export: `': not a valid identifier\n", PROGRAM_NAME);
		data->err_code = EXIT_FAILURE;
		(*i)++;
	}
	else if (is_flag(cmd->args[1]))
	{
		printf("%s export: %c%c: invalid option\n", PROGRAM_NAME,
			cmd->args[1][0], cmd->args[1][1]);
		printf("export: usage: export [no options admitted]");
		printf(" [name[=value] ...]\n");
		data->err_code = 2;
		(*i)++;
	}
}

/* 
It checks whether the built-in has any operators in its arguments,
If yes, prepares to concatenate or substitute the value. 
If not, an error message is printed. 
*/
void	export_actions(t_data *data, t_cmd *cmd)
{
    int     i;
    int     operator_type;
    int     var_in_env;

    operator_type = valid_varname(cmd->args[i]);
    if (operator_type)
    {
        if (operator_type == 2)
            remove_plus(cmd->args[i]);
        var_in_env = check_if_exist(data->env, cmd->args[i]);
        if (operator_type == 1 || operator_type == 3)
            export_var(data, cmd->args[i]);
        else if (operator_type == 2)
            prepare_to_join(data, cmd->args[i]);
    }
    else
    {
        if (cmd->args[i][0])
			printf("%s export: ", PROGRAM_NAME);
            printf("%s : not a valid identifier\n", cmd->args[i]);
            data->err_code = EXIT_FAILURE;
    }
}

/* 
- add variable de entorno.
- si ya existe, sobreescribe.
- si no hay argumentos, imprime todas las variables de entorno.
- si hay argumentos, imprime las variables de entorno que coincidan.
 */

/* It checks whether the built-in has any operators in its arguments,
    and if so, prepares to concatenate or substitute the value. 
    If not, an error message is printed. 

    Return: int - Returns the value of the exit_status, which will depend on
    each case. In case of success, the value is 0.
*/
void    run_export(t_data *data, t_cmd *cmd)
{
    int     i;

    data->err_code = EXIT_SUCCESS;
    if (!cmd->args[i])
        //print all env vars
        copy_env(data->env, data);
    i = 0;
    /*Checks if the command received as argument is an empty string or
 	if it is a flag, to print the corresponding error messages.
    */
    check_cmd(cmd, i, data);
    if (data->err_code == 2)
        return (data->err_code);
    while (cmd->args && cmd->args[i])
    {
        //add or update env var
        export_action(data, cmd);
        i++;
    }
    return (data->err_code);
}