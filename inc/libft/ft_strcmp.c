

#include "libft.h"

int	ft_strcmp(char *ehe, char *cmp)
{
	int	i;

	i = 0;
	while (ehe[i] && cmp[i])
	{
		if (ehe[i] != cmp[i])
			return (ehe[i] - cmp[i]);
		i++;
	}
	if ((ehe[i] && !cmp[i]) || (cmp[i] && !ehe[i]))
		return (ehe[i] - cmp[i]);
	return (0);
}