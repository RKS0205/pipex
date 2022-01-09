/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 19:21:33 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/01/08 18:56:14 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		write (STDERR, "Invalid number of arguments\n", 28);
		exit(1);
	}
	if (argv[1][0] == '\0' || argv[2][0] == '\0' ||
			argv[3][0] == '\0' || argv[4][0] == '\0')
	{
		write (STDERR, "Empty string\n", 13);
		exit(1);
	}
}

void	open_files(char **argv, t_data *data)
{
	if (access(argv[4], F_OK) == -1)
		data->fdout = open(argv[4], O_CREAT | O_WRONLY);
	else
		data->fdout = open(argv[4], O_WRONLY | O_TRUNC);
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

void	first_command(t_data *data, char **argv, char **env)
{
	close(data->pipefd[0]);
	dup2(data->pipefd[1], STDOUT);
	data->cmd = get_cmd(argv[2]);
	data->path = get_path(data, env);
	execve(data->path, data->cmd, env);
}

void	second_command(t_data *data, char **argv, char **env)
{
	close(data->pipefd[1]);
	dup2(data->pipefd[0], STDIN);
	data->cmd = get_cmd(argv[3]);
	data->path = get_path(data, env);
	execve(data->path, data->cmd, env);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	int		pid;

	check_args(argc, argv);
	data = (t_data *) malloc (sizeof(t_data));
	open_files(argv, data);
	dup2(data->fdout, STDOUT);
	dup2(data->fdin, STDIN);
	if (pipe(data->pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		first_command(data, argv, env);
	else
		second_command(data, argv, env);
}
