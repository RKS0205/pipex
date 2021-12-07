#include "../pipex.h"

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return (n);
}

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
		{
			matriz[strcount] = ft_substr(s, start, n - start);
			strcount++;
		}
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

char	*ft_strjoin(char const *s1, char const *s2)
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
	{
		s[count] = s2[count2];
		count++;
		count2++;
	}
	s[count] = '\0';
	return (s);
}

char	*get_path(char **cmd, char **env)
{
	int i;
	char	*line;
	char	**check;
	char	*path;

	i = 0;
	while (env[i][0] != 'P' || env[i][1] != 'A' || env[i][2] != 'T' || env[i][3] != 'H')
		i++;
	line = env[i] + 5;
	check = ft_split(line, ':');
	i = 0;
	path = 0;
	while (check[i] != NULL)
	{
		path = ft_strjoin(check[i], cmd[0]);
			if (access(path, F_OK) == -1)
				free (path);
			else
			{
				free (check);
				return (path);
			}
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	int	pid;
	int	fdin;
	int fdout;
	char	**cmd;

	if (argc != 5)
		write (2, "Invalid number of arguments", 27);
	else
	{
		if (access(argv[1], F_OK) == -1)
			fdin = open(argv[1], O_CREAT);
		else
			fdin = open(argv[1], O_RDONLY);
		if (access(argv[4], F_OK) == -1)
			fdout = open(argv[4], O_CREAT | O_WRONLY);
		else
			fdout = open(argv[4], O_WRONLY);
		if (pipe(pipefd) == -1)
			return (-1);
		cmd = ft_split(argv[2], ' ');;
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT);
			dup2(fdin, STDIN);
			cmd = ft_split(argv[2], ' ');
			execve(get_path(cmd, env), cmd, env);
		}
		else
		{
			close(pipefd[1]);
			dup2(fdout, STDOUT);
			dup2(pipefd[0], STDIN);
			cmd = ft_split(argv[3], ' ');
			execve(get_path(cmd, env), cmd, env);
		}
	}
	return (0);
}