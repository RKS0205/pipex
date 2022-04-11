/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 01:17:45 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/01/09 01:17:45 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

static char	*read_loop(int fd, char *buff, char *str)
{
	int	size;

	size = 1;
	while (!ft_strchr(buff, '\n') && size != 0)
	{
		size = read(fd, buff, 1);
		if (size == -1)
		{
			free (buff);
			free (str);
			return (NULL);
		}
		buff[size] = '\0';
		str = ft_my_strjoin(str, buff);
	}
	return (str);
}

static char	*get_big_line(int fd, char *str)
{
	char	*buff;

	if (!str)
	{
		str = malloc (sizeof(char) * 1);
		str[0] = '\0';
	}
	buff = (char *) malloc (sizeof(char) * 1 + 1);
	if (!buff)
		return (NULL);
	buff[0] = '\0';
	str = read_loop (fd, buff, str);
	if (str == NULL)
		return (NULL);
	free (buff);
	if (str[0] == '\0')
	{
		free (str);
		return (NULL);
	}
	return (str);
}

static char	*get_line(char	*big_line)
{
	char	*line;
	int		count;

	count = 0;
	while (big_line[count] != '\0' && big_line[count] != '\n')
		count++;
	line = ft_substr(big_line, 0, count + 1);
	return (line);
}

static char	*get_str(char *big_line)
{
	int		count;
	char	*new_str;

	count = 0;
	while (big_line[count] != '\0' && big_line[count] != '\n')
		count++;
	if (big_line[count] == '\n' && big_line[count + 1] != '\0')
	{
		count++;
		new_str = ft_substr(big_line, count, ft_strlen(big_line) - count);
		free (big_line);
		return (new_str);
	}
	free (big_line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*big_line;

	if (fd < 0 || fd > 256)
		return (NULL);
	else
	{
		big_line = get_big_line(fd, str);
		if (big_line == NULL)
			return (NULL);
		line = get_line(big_line);
		str = get_str(big_line);
		return (line);
	}
}
