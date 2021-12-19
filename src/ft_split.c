/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:21:19 by rkenji-s          #+#    #+#             */
/*   Updated: 2021/12/19 19:21:19 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

static int	my_count(char *s, char c)
{
	int	count;
	int	n;

	n = 0;
	count = 0;
	while (s[n] != '\0')
	{
		if (s[n] != c && (s[n + 1] == c || s[n + 1] == '\0'))
			count++;
		n++;
	}
	return (count);
}

static void	my_string(char	*s, char c, char **matriz)
{
	int	n;
	int	start;
	int	strcount;

	n = 0;
	start = 0;
	strcount = 0;
	while (s[n] != '\0')
	{
		while (s[n] == c)
			n++;
		start = n;
		while (s[n] != c && s[n] != '\0')
			n++;
		if ((s[n] == c || s[n] == '\0') && s[n - 1] != c)
			matriz[strcount++] = ft_substr(s, start, n - start);
	}
}

char	**ft_split(char const *s, char c)
{
	char	**matriz;
	int		count;

	count = my_count((char *)s, c);
	matriz = (char **) malloc (sizeof(char *) * (count + 1));
	if (matriz == NULL)
		return (NULL);
	my_string((char *) s, c, matriz);
	matriz[count] = NULL;
	return (matriz);
}
