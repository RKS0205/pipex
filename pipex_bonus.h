/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:14:53 by rkenji-s          #+#    #+#             */
/*   Updated: 2021/12/19 23:14:53 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	int		fdin;
	int		fdout;
	int		pipefd[2];
	char	**cmd;
	char	*path;

}	t_data;

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	**get_cmd(char *s);
char	*get_path(t_data *data, char **env);
char	*my_path_join(char const *s1, char const *s2);
void	free_split(char **s);
int		str_check(const char *s1, const char *s2);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif