/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 23:13:34 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/01/09 03:58:09 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 5)
	{
		write (STDERR, "Invalid number of arguments", 27);
		exit(1);
	}
	while (argv[i] != NULL)
	{
		if (argv[i++][0] == '\0')
		{
			write (STDERR, "Empty string\n", 13);
			exit(1);
		}
	}
}

void	here_doc_open(char **argv, t_data *data, int argc)
{
	char	*line;
	int		fd;

	if (access(argv[argc - 1], F_OK) == -1)
		data->fdout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		data->fdout = open(argv[argc - 1], O_WRONLY | O_APPEND);
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = get_next_line(STDIN);
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2]) != 0))
			write (fd, line, ft_strlen(line));
		else
		{
			free (line);
			close(fd);
			data->fdin = open(".here_doc", O_RDONLY);
			return ;
		}
		free(line);
	}
}

void	open_files(char **argv, t_data *data, int argc)
{
	if (access(argv[argc - 1], F_OK) == -1)
		data->fdout = open(argv[argc - 1], O_CREAT | O_WRONLY, 0644);
	else
		data->fdout = open(argv[argc - 1], O_WRONLY | O_TRUNC);
	if (access(argv[1], F_OK | R_OK) == -1)
	{
		write (STDERR, argv[1], ft_strlen(argv[1]));
		write (STDERR, ": No such file or directory\n", 28);
		free(data);
		exit(1);
	}
	else
		data->fdin = open(argv[1], O_RDONLY);
}

void	cmd_loop(t_data *data, char **argv, char **env, int count)
{
	int	pid;

	if (pipe(data->pipefd) == -1)
		exit (1);
	pid = fork();
	if (pid == 0)
	{
		close(data->pipefd[0]);
		dup2(data->pipefd[1], STDOUT);
		data->cmd = get_cmd(argv[count]);
		data->path = get_path(data, env);
		execve(data->path, data->cmd, env);
	}
	else
	{
		close(data->pipefd[1]);
		dup2(data->pipefd[0], STDIN);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		count;

	check_args(argc, argv);
	data = (t_data *) malloc (sizeof(t_data));
	count = 2;
	if (ft_strncmp("here_doc", argv[1], 9) == 0 && count++)
		here_doc_open(argv, data, argc);
	else
		open_files(argv, data, argc);
	if (fork() == 0)
	{
		dup2(data->fdout, STDOUT);
		dup2(data->fdin, STDIN);
		while (count < argc - 2)
			cmd_loop(data, argv, env, count++);
		data->cmd = get_cmd(argv[count]);
		data->path = get_path(data, env);
		execve(data->path, data->cmd, env);
	}
	wait(NULL);
	close(data->fdin);
	close(data->fdout);
	free(data);
	unlink(".here_doc");
}
