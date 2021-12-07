#include "../pipex.h"

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	int	pid;
	int	fdin;
	int fdout;
	char* b[] = {"grep", "hello", NULL};
	char* a[] = {"wc", "-l", NULL};

	if (argc != 5)
		write (2, "Invalid number of arguments", 27);
	else
	{
		if (access(argv[1], F_OK) == -1)
			fdin = open(argv[1], O_CREAT | O_WRONLY);
		else
			fdin = open(argv[1], O_RDONLY);
		if (access(argv[4], F_OK) == -1)
			fdout = open(argv[4], O_CREAT | O_WRONLY);
		else
			fdout = open(argv[4], O_WRONLY);
		if (pipe(pipefd) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT);
			dup2(fdin, STDIN);
			execve("/usr/bin/grep", b, env);
		}
		else
		{
			close(pipefd[1]);
			dup2(fdout, STDOUT);
			dup2(pipefd[0], STDIN);
			execve("/usr/bin/wc", a, env);
		}
	}
	return (0);
}