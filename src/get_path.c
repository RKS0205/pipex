/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:21:30 by rkenji-s          #+#    #+#             */
/*   Updated: 2021/12/19 19:21:30 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	path_error(char **check, t_data *data)
{
	free_split(check);
	write (STDERR, data->cmd[0], ft_strlen(data->cmd[0]));
	write (STDERR, ": command not found\n", 20);
	free_split(data->cmd);
	free(data);
}

char	*my_path_join(char const *s1, char const *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = 0;
	count2 = 0;
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[count] != '\0')
	{
		s[count] = s1[count];
		count++;
	}
	s[count++] = '/';
	while (s2[count2] != '\0')
		s[count++] = s2[count2++];
	s[count] = '\0';
	return (s);
}

char	*get_path(t_data *data, char **env)
{
	int		i;
	char	*line;
	char	**check;
	char	*path;

	i = 0;
	while (env[i][0] != 'P' || env[i][1] != 'A'
			|| env[i][2] != 'T' || env[i][3] != 'H')
		i++;
	line = env[i] + 5;
	check = ft_split(line, ':');
	i = 0;
	while (check[i] != NULL)
	{
		path = my_path_join(check[i], data->cmd[0]);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_split(check);
			return (path);
		}
		free(path);
		i++;
	}
	path_error(check, data);
	exit (127);
}
