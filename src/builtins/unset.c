/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:13:05 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/12/19 17:10:12 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
Check that the variable passed as an argument actually matches
one of the variables in data->env.

Ret 0 if it matches.
 */
int	ft_cmp_varname(char *s, char **env, int *num_env)
{
	int	i;
	int	j;

	i = 0;
	if (!s | !*s)
		return (1);
	while (env && env[i])
	{
		j = 0;
		while (s[j] && env[i][j] && env[i][j] != '=' && s[j] == env[i][j])
			j++;
		if (s[j] == '\0' && (env[i][j] == '=' || env[i][j] == '\0'))
		{
			*num_env = i;
			return (0);
		}
		i++;
	}
	return (1);
}

/*
Frees the pointer of the KEY to be removed and moves all subsequent
strings, one position -1. 
*/
void    remove_var(char **env, int *num_env)
{
    int i;
    
    i = *num_env;
    while (*num_env >= 0 && env[*num_env])
    {
        if (i == *num_env)
            free(env[i]);
        env[i] = env[i + 1];
    }
    env[i - 1] = NULL;
}


/*
Removes the environment variables with the given keys
after checking if they are valid keys.
Does nothing if the key is not in the environment.

Ret: EXIT_SUCCESS if the command is executed correctly.
 */
int	run_unset(char **cmd, t_data *data)
{
	int	i;
	int	num_env;

	num_env = 0;
	i = 0;
	while (cmd[i])
		i++;
	if (i == 1)
		return (EXIT_SUCCESS);
	i = 1;
	while (cmd[i] && cmd)
	{
		if (is_flag(cmd[1]))
		{
			printf("%s unset: %c%c: invalid option\n", PROGRAM_NAME,
				*(cmd[i]), *(cmd[i] + 1));
			printf("unset: usage: unset [no options admitted] [name ...]\n");
			return (2);
		}
		else if (ft_cmp_varname(cmd[i], data->env, &num_env) == 0)
			remove_var(data->env, &num_env);
		i++;
	}
	return (EXIT_SUCCESS);
}