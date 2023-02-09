/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonusnew.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/09 17:23:21 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child(t_data *data, int rd, int wr)
{
	if (data->nb_cmd == data->ac - 2)
	{
		if (dup2(data->out, STDOUT_FILENO) == -1)
			ft_exit();
	}
	else
	{
		if (dup2(wr, STDOUT_FILENO) == -1)
			ft_exit();
	}
	if (close(rd) == -1 || close(wr) == -1)
	{
		ft_exit();
	}
	ft_access(data);
	if (execve(data->cmd_path, data->cmd_args, data->env) == -1)
	{
		ft_putstr_fd("Error command not found : ", 2);
		ft_putendl_fd(data->cmd_args[0], 2);
		exit(127);
	}
}

void	ft_parent(t_data *data, int rd, int wr)
{
	if (data->in == -1)
		ft_exit();
	else if (data->nb_cmd == 2)
	{
		if (dup2(data->in, STDIN_FILENO) == -1)
			ft_exit();
	}
	else
	{
		if (dup2(rd, STDIN_FILENO) == -1)
			ft_exit();
	}
	if (close(rd) == -1 || close(wr) == -1)
		ft_exit();
}

void	ft_process(t_data *data, t_pid **lst_pid)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit();
	data->pid = fork();
	if (data->pid == -1)
		ft_exit();
	ft_lstadd_back(lst_pid, ft_lstnew((void *)&data->pid));
	if (data->pid == 0)
	{
		ft_child(data, fd[0], fd[1]);
	}
	else
	{
		ft_parent(data, fd[0], fd[1]);
	}
}
