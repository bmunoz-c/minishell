/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:50:47 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/11/18 19:19:16 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_env(t_env *env)
{
	printf(BLUE "---------- PRINTING ENV -----------" RESET "\n");
	if (!env)
		printf("env is empty\n");
	while (env)
	{
		printf(GREEN "key: %s \t\tvalue: %s" RESET "\n", env->key, env->value);
		env = env->next;
	}
	printf(BLUE "--------- END PRINT ENV -----------" RESET "\n");
}

void	print_cmd(t_cmd *cmd)
{
	int	i;

	printf(MAGENTA "---------- PRINTING CMDs -----------" RESET "\n");
	if (!cmd)
		printf("cmd is empty\n");
	while (cmd)
	{
		if (cmd->path)
			printf(YELLOW "path: %s\n [%d] -" RESET, cmd->path, cmd->nargs);
		else
			printf(YELLOW "path: undefined\n [%d] -" RESET, cmd->nargs);
		i = 0;
		if (cmd->args)
		{ // Check if cmd->args is valid
			while (cmd->args[i])
			{ // Check each argument for validity
				printf(CYAN "|%s|, " RESET, cmd->args[i]);
				i++;
			}
		}
		else
			printf(CYAN "args: undefined\n" RESET);
		if (cmd->input_file)
			printf(RED "\n in: %s" RESET, cmd->input_file);
		else
			printf(RED "\n in: undefined" RESET);
		if (cmd->output_file)
			printf(RED " out: %s\n" RESET, cmd->output_file);
		else
			printf(RED " out: undefined\n" RESET);
		cmd = cmd->next;
	}
	printf(MAGENTA "--------- END PRINT CMDs -----------" RESET "\n");
}
char *get_tokentype(int n)
{
	switch (n)
	{
		case WORD: return "WORD";
		case SPC: return "SPC";
		case PIPE: return "PIPE";
		case SQ_STR: return "SQ_STR";
		case DQ_STR: return "DQ_STR";
		case ENV_VAR: return "ENV_VAR";
		case HERE_DOC: return "HERE_DOC";
		case INPUT: return "INPUT";
		case OUTPUT: return "OUTPUT";
		case APPEND: return "APPEND";
	}
	return (NULL);
}

void	print_token(t_token *token)
{
	printf(BLUE "Token_Dir %p\n" RESET, token);
	printf(GREEN "Type: %s\n" RESET, get_tokentype(token->type));
	printf(CYAN "Content: ~%s~\n" RESET, token->content);
	printf(YELLOW "Next dir: %p\n" RESET, token->next);
	printf(MAGENTA "Prev dir: %p\n" RESET, token->prev);
	printf(RED "**********************************" RESET "\n");
}




void	print_token_list(t_token *token_list)
{
	t_token	*tmp;
	int i;

	printf(CYAN "********* PRINTING TOKENS *********" RESET "\n");
	i = 0;
	tmp = token_list;
	if(!tmp)
		printf("token list is empty\n");
	while (tmp)
	{
		print_token(tmp);
		tmp = tmp->next;
		i++;
	}
	printf(CYAN "Tkn count: %d\n" RESET, i);
	printf(CYAN "********* END PRINT TOKEN *********" RESET "\n");
}