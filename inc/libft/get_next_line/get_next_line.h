/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:36:37 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/05/05 20:26:03 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	save_next(t_list **lst);
char	*save_line(t_list **lst);
void	read_fd(int fd, t_list **lst);
int		has_nl(t_list *lst);
t_list	*last_node(t_list *lst);
t_list	*add_node(t_list **lst, char *content);
int		index_newline(t_list *lst);
void 	clear_lst(t_list **lst);



#endif