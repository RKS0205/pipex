#ifndef PIPEX_H
# define PIPEX_H
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
	int	fdin;
	int	fdout;
	int	pipefd[2];

}	t_data;

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
char	**get_cmd(char *s);

#endif