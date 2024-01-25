/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:14:53 by bszabo            #+#    #+#             */
/*   Updated: 2023/10/09 11:14:55 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// look for character 'c' in string 'str'
// if found, return pointer to character
// if not found, return NULL
char	*ft_strchr(const char *str, int c)
{
	unsigned char	c_c;

	if (!str)
		return (NULL);
	c_c = (unsigned char)c;
	while (*str)
	{
		if (c_c == *str)
			return ((char *)str);
		str++;
	}
	if (c_c == '\0')
		return ((char *)str);
	return (0);
}

// return length of string 'str'
size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

// join s1 and s2 into a new string and return it
char	*gnl_strjoin(char *s1, char *s2)
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
