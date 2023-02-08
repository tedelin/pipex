/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/08 19:47:26 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exec(t_data *data)
{
	ft_access(data);
	if (execve(data->cmd_path, data->cmd_args, data->env) == -1)
	{
		ft_putstr_fd("Error command not found : ", 2);
		ft_putendl_fd(data->cmd_args[0], 2);
		exit(127);
	}
}

void	ft_cmd(t_data *data, t_list **lst_pid)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit();
	data->nb_cmd++;
	data->pid = fork();
	if (data->pid == -1)
		ft_exit();
	ft_lstadd_back(lst_pid, ft_lstnew((void *)&data->pid));
	if (data->pid == 0)
	{
		ft_pipe(data, fd[0], fd[1]);
		ft_exec(data);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit();
		if (close(fd[1]) == -1 || close (fd[0]) == -1)
			ft_exit();
	}
}

void	ft_pipe(t_data *data, int rd, int wr)
{
	if (data->nb_cmd == 2)
	{
		if (data->in == -1)
			ft_exit();
		if (dup2(data->in, STDIN_FILENO) == -1 || dup2(wr, STDOUT_FILENO) == -1)
			ft_exit();
	}
	else if (data->nb_cmd == data->ac - 2)
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
		ft_exit();
}
