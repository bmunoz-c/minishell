/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:50:47 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/11 13:29:45 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *env)
{
	printf("---------- PRINTING ENV -----------\n");
	while (env)
	{
		printf("key: %s \t\tvalue: %s\n", env->key, env->value);
		env = env->next;
	}
	printf("--------- END PRINT ENV -----------\n");
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf("---------- PRINTING CMDs -----------\n");
	while (cmd)
	{
		if (cmd->path)
			printf("path: %s\n [%d] -", cmd->path, cmd->nargs);
		else
			printf("path: undefined\n [%d] -", cmd->nargs);
		i = 0;
		if (cmd->args)
		{ // Check if cmd->args is valid
			while (cmd->args[i])
			{ // Check each argument for validity
				printf("|%s|, ", cmd->args[i]);
				i++;
			}
		}
		else
		{
			printf("args: undefined\n");
		}
		if (cmd->input_file)
			printf("\n in: %s", cmd->input_file);
		else
			printf("\n in: undefined");
		if (cmd->output_file)
			printf(" out: %s", cmd->output_file);
		else
			printf(" out: undefined\n");
		cmd = cmd->next;
	}
	printf("--------- END PRINT CMDs -----------\n");
}
