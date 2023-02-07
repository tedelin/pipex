/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 16:59:15 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_first(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit();
	data->pid = fork();
	if (data->pid == -1)
		ft_exit();
	if (data->pid == 0)
	{
		if (data->in == -1)
			ft_exit();
		else if (dup2(data->in, STDIN_FILENO) == -1 || dup2(fd[1], STDOUT_FILENO) == -1)
			ft_exit();
		close(fd[0]);
		close(fd[1]);
		if (ft_exec(data, 3))
			ft_exit();
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit();
		close(fd[0]);
	}
}

void	ft_last(t_data *data)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit();
	data->pid = fork();
	if (data->pid == -1)
		ft_exit();
	if (data->pid == 0)
	{
		close(fd[0]);
		if (dup2(data->out, STDOUT_FILENO) == -1)
			ft_exit();
		close(fd[1]);
		if (ft_exec(data, 3))
			ft_exit();
	}
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit();
		close(fd[0]);
	}
}
