/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmunoz-c <bmunoz-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:19:03 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/18 21:20:14 by bmunoz-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Merge tokens of type WORD, SQ_STR, DQ_STR.
// Quitar espacios y tokens vacios.
// Check sintax errors.