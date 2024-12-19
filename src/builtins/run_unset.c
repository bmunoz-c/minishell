/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: borjamc <borjamc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:40 by borjamc           #+#    #+#             */
/*   Updated: 2024/12/19 17:39:44 by borjamc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the variable passed as an argument matches one in data->env.
// Returns 0 if it matches.
int ft_cmp_varname(char *s, t_env *env)
{
    t_env *current;

    if (!s || !*s)
        return (1);

    current = env;
    while (current)
    {
        if (strcmp(s, current->key) == 0)
        {
            current->match = 1;
            return (0);
        }
        current = current->next;
    }
    return (1);
}

// Frees the environment variable and removes it from the linked list.
void remove_var(t_env **env)
{
    t_env *current;
    t_env *prev;
    t_env *tmp;

    current = *env;
    prev = NULL;
    while (current)
    {
        if (current->match)
        {
            if (prev)
                prev->next = current->next;
            else
               *env = current->next;
        tmp = current;
        current = current->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

// Removes the environment variables with the given keys.
// Does nothing if the key is not in the environment.
// Returns EXIT_SUCCESS if executed correctly.
int run_unset(char **cmd, t_data *data)
{
    int i;
    t_env *current;

    if (!cmd || !cmd[1])
        return (EXIT_SUCCESS);

    i = 1;
    while (cmd[i])
    {
        if (is_flag(cmd[i]))
        {
            printf("%s unset: %c%c: invalid option\n", PROGRAM_NAME, *(cmd[i]), *(cmd[i] + 1));
            printf("unset: usage: unset [no options admitted] [name ...]\n");
            return (2);
        }
        else if (ft_cmp_varname(cmd[i], data->env) == 0)
        {
            current = data->env;
            while (current)
            {
                if (ft_strcmp(cmd[i], current->key) == 0)
                {
                    current->match = 1;
                    break ;
                }
                current = current->next;
            }
        }
        i++;
    }
    remove_var(&data->env);
    return (EXIT_SUCCESS);
}