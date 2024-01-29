/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 10:44:03 by bszabo            #+#    #+#             */
/*   Updated: 2023/09/10 10:51:50 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// concatenate s1 and s2 into s_final
static char	*concat_strs(char *s1, char *s2, char *s_final)
{
	int	i;
	int	j;

	i = -1;
	while (s1[++i])
		s_final[i] = s1[i];
	j = 0;
	while (s2[j])
		s_final[i++] = s2[j++];
	s_final[i] = '\0';
	return (s_final);
}

// join s1 and s2 into a new string with malloc and return it
char	*ft_strjoin(char *s1, char *s2)
{
	char	*s_final;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	s_final = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (s_final == NULL)
	{
		free(s1);
		return (NULL);
	}
	s_final = concat_strs(s1, s2, s_final);
	free(s1);
	return (s_final);
}
/*
#include <stdio.h>
int main(void)
{
	char *s1 = "hello";
	char *s2 = "World";
	char *res = ft_strjoin(s1, s2);
	printf("%s + %s = %s\n", s1, s2, res);
	printf("    s1 memory: %p\nresult memory: %p\n", (void *)&s1, (void *)&s2);
	free(res);
	return (0);
}
*/
