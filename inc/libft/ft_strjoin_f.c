/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:04:16 by bmunoz-c          #+#    #+#             */
/*   Updated: 2024/11/19 12:07:22 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*ft_strjoin_f(char *s1, char *s2, char *s1_f, char *s2_f)
{
	char	*join;
	size_t	s1len;
	size_t	s2len;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!join)
		return (NULL);
	if (s1)
		ft_strlcpy(join, s1, s1len + 1);
	if (s2)
		ft_strlcpy(join + s1len, s2, s2len + 1);
	free_ptr(s1_f);
	free_ptr(s2_f);
	return (join);
}
/*
int	main(void)
{
	char s1[] = "Hola ";
	char s2[] = "mundo!";
	printf("%s\n", ft_strjoin(s1, s2));
	return (0);
}
*/
