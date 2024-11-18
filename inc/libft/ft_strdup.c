/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:25:56 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/18 13:44:41 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	size;

	if(!s1)
		return (NULL);
	size = ft_strlen(s1);
	s2 = malloc(size * sizeof(char) + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, size + 1);
	return (s2);
}
