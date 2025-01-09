/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:40 by borjamc           #+#    #+#             */
/*   Updated: 2025/01/09 19:54:06 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the variable passed as an argument matches one in data->env.
// Returns 0 if it matches.
t_env *ft_cmp_varname(char *s, t_env *env)
{
    t_env *current;

    if (!s || !*s)
        return (NULL);

    current = env;
    while (current)
    {
        if (ft_strncmp(s, current->key, ft_strlen(s) + 1) == 0)
        {
            current->match = 1;
            return (current);
        }
        current = current->next;
    }
    return (NULL);
}

// Frees the environment variable and removes it from the linked list.
void remove_var(t_data *data, t_env *current)
{
    if(!current)
        return;
    if(current->prev)
        current->prev->next = current->next;
    else
        data->env = current->next;
    if(current->next)
        current->next->prev = current->prev;
    else
        current->prev->next = NULL;
    current->next = NULL;   
    current->prev = NULL;
    free_env(current);
    print_env(data->env);
    ft_free_split(data->env_matrix);
    data->env_matrix = env_as_matrix(data->env, data->env_matrix);
}

// Removes the environment variables with the given keys.
// Does nothing if the key is not in the environment.
// Returns EXIT_SUCCESS if executed correctly.
int run_unset(char **cmd, t_data *data)
{
    int i;

    if (!cmd || !cmd[1])
        return (EXIT_SUCCESS);
    i = 1;
    if(search_flags(cmd, "unset"))
        return (2);
    while (cmd[i])
        remove_var(data, ft_cmp_varname(cmd[i++], data->env));
    return (EXIT_SUCCESS);
}
