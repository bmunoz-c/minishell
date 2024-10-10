/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:45:17 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/10/10 17:03:09 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

//_____FLAGS_____//
typedef struct s_quotes_flag
{
	int	simple;
	int	doubles;
}	t_quotes_flag;

//_____UTILS_____//
void	check_quotes(t_quotes_flag *quotes, char c);
int		avoid_quotes(char *str, int *i);
int		is_starting_quote(char c, t_quotes_flag *quotes);

#endif
