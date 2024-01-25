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

// join strings 's1' and 's2' into a new string with malloc
// return pointer to new string
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_final;
	int		s_len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_len = (int)(ft_strlen(s1) + ft_strlen(s2));
	s_final = (char *)malloc(s_len + 1);
	if (s_final == NULL)
		return (NULL);
	while (s1[i])
	{
		s_final[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s_final[i] = s2[j];
		i++;
		j++;
	}
	s_final[i] = '\0';
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
