/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:45:11 by jsebasti          #+#    #+#             */
/*   Updated: 2025/01/31 10:52:09 by jsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_delimiter(t_token *tk)
{
	// t_token	*delimiter;
	t_token	*tk_list;
	char	*del;

	merge_tokens(&tk);
	tk_list = tk->next;
	// delimiter = new_token(tk->content, tk->type);
	// if (tk->next && (tk->next->type == DQ_STR || tk->next->type == SQ_STR
	// 		|| tk->next->type == WORD))
	// {
	// 	free_token(delimiter);
	// 	delimiter = merge_tokens(&tk_list);
	// 	if (!delimiter)
	// 		delimiter = new_token(tk->content, tk->type);
	// }
	del = ft_strdup(tk_list->content);
	// free_token(delimiter);
	return (del);
}

void	exec_here(t_token *delimiter)
{
	int			pid;
	int			status;
	int			fd;
	char		*del;

	fd = open(HEREDOC_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		del = get_delimiter(delimiter);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		print_here(del, fd);
		free(del);
		exit(0);
	}
	wait(&status);
	g_sig_exit_status = WEXITSTATUS(status);
	signal(SIGINT, handle_signal_prompt);
	signal(SIGQUIT, SIG_IGN);
	close(fd);
}

void	print_here(const char *del, int fd)
{
	char	*line;
	int		n_line;

	line = readline("> ");
	n_line = 1;
	while (line != NULL && ft_strncmp(line, del, ft_strlen(del) + 1))
	{
		ft_putendl_fd(line, fd);
		free_ptr(line);
		n_line++;
		line = readline("> ");
	}
	if (!line)
	{
		line = ft_itoa(n_line);
		ft_putstr_fd("warning: here-document at line ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd(" delimited by end-of-file (wanted\'", 2);
		ft_putstr_fd(del, 2);
		ft_putstr_fd("\')\n", 2);
	}
	free_ptr(line);
}

int	check_heredoc(t_token *tk_lst, t_data *data)
{
	t_token	*tk;
	t_token	*tmp_del;

	tk = tk_lst;
	while (tk)
	{
		if (tk->type == HERE_DOC)
		{
			tmp_del = tk->next;
			while (tmp_del->type == SPC)
				tmp_del = tmp_del->next;
			if (tmp_del->type != WORD && tmp_del->type != DQ_STR
				&& tmp_del->type != SQ_STR)
			{
				syntax_error_msg(data, "heredoc");
				return (0);
			}
			exec_here(tk);
		}
		tk = tk->next;
	}
	return (1);
}
