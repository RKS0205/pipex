#include "../pipex.h"

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
		path = my_path_join(check[i], cmd[0]);
		if (access(path, F_OK) == -1)
			free (path);
		else
		{
			free (check);
			return (path);
		}
		i++;
	}
	free (check);
	free (path);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		pid;
	char	**cmd;

	if (argc != 5)
		write (2, "Invalid number of arguments", 27);
	else
	{
		data = (t_data *) malloc (sizeof(t_data));
		if (access(argv[1], F_OK) == -1)
			data->fdin = open(argv[1], O_CREAT);
		else
			data->fdin = open(argv[1], O_RDONLY);
		if (access(argv[4], F_OK) == -1)
			data->fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC);
		else
			data->fdout = open(argv[4], O_WRONLY | O_TRUNC);
		if (pipe(data->pipefd) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			close(data->pipefd[0]);
			dup2(data->pipefd[1], STDOUT);
			dup2(data->fdin, STDIN);
			cmd = get_cmd(argv[2]);
			if (execve(get_path(cmd, env), cmd, env) == -1)
			{
				free(cmd);
				perror("command not found loser idiot");
				exit (127);
			}
		}
		else
		{
			close(data->pipefd[1]);
			dup2(data->fdout, STDOUT);
			dup2(data->pipefd[0], STDIN);
			cmd = get_cmd(argv[3]);
			if (execve(get_path(cmd, env), cmd, env) == -1)
			{
				free(cmd);
				perror("command not found loser idiot");
				exit (127);
			}
		}
	}
	close(data->fdin);
	close(data->fdout);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	return (0);
}
