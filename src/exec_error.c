/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkenji-s <rkenji-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:02:50 by rkenji-s          #+#    #+#             */
/*   Updated: 2022/01/15 17:02:50 by rkenji-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	exec_error(t_data *data)
{
	write(STDERR, "Error executing ", 16);
	write(STDERR, data->cmd[0], ft_strlen(data->cmd[0]));
	close(data->fdin);
	close(data->fdout);
	free_split(data->cmd);
	free(data->path);
	free(data);
	exit(1);
}