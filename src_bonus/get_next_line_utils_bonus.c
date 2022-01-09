/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:17:40 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/01/09 01:17:40 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		s[count] = s1[count];
		count++;
	}
	while (s2[count2] != '\0')
	{
		s[count] = s2[count2];
		count++;
		count2++;
	}
	free (s1);
	s[count] = '\0';
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (c > 255)
		c -= 256;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return (NULL);
}
