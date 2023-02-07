/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 14:03:21 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_middle(t_data *data, t_list **lst_pid)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("Pipe ");
		exit(errno);
	}
	data->cmd++;
	pid = fork();
	ft_lstaddback(lst_pid, ft_lstnew((void *)pid));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_exec(data, data->cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	ft_first(t_data *data, t_list **lst_pid)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("Pipe ");
		exit(errno);
	}
	data->cmd++;
	pid = fork();
	ft_lstaddback(lst_pid, ft_lstnew((void *)pid));
	if (pid == 0)
	{
		dup2(data->in, STDIN_FILENO);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_exec(data, data->cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}

void	ft_last(t_data *data, t_list **lst_pid)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("Pipe ");
		exit(errno);
	}
	data->cmd++;
	pid = fork();
	ft_lstaddback(lst_pid, ft_lstnew((void *)pid));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(data->out, STDOUT_FILENO);
		close(fd[1]);
		ft_exec(data, data->cmd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
