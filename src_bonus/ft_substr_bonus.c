/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:13:53 by rkenji-s          #+#    #+#             */
/*   Updated: 2021/12/19 23:13:53 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static size_t	my_count2(char const *s, unsigned int start, size_t len)
{
	size_t	count;
	size_t	a;

	a = 0;
	count = 0;
	while (s[a] != '\0')
	{
		if (a >= start && count < len)
			count++;
		a++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	a;
	size_t	b;
	size_t	count;

	a = 0;
	b = 0;
	count = my_count2(s, start, len);
	str = (char *) malloc (sizeof(char) * count + 1);
	if (str == NULL)
		return (NULL);
	while (s[a] != '\0')
	{
		if (a >= start && b < len)
		{
			str[b] = s[a];
			b++;
		}
		a++;
	}
	str[b] = '\0';
	return (str);
}
