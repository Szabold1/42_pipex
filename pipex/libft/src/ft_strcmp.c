#include "../include/libft.h"

// compare 's1' and 's2', return 0 if they are identical
// if 's1' < 's2' return negative number, if 's1' > 's2' return positive number
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] - s2[i] != 0)
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
