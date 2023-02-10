/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/10 12:56:21 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_process(t_data *data, t_pid **lst_pid)
{
	int		fd[2];

	if (pipe(fd) == -1)
		ft_exit(data, lst_pid, NULL);
	data->pid = fork();
	if (data->pid == -1)
		ft_exit(data, lst_pid, NULL);
	if (data->pid == 0)
	{
		ft_child(data, lst_pid, fd[0], fd[1]);
	}
	else
	{
		pid_lstadd_back(lst_pid, pid_lstnew(data->pid));
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit(data, lst_pid, NULL);
		if (close(fd[1]) == -1 || close (fd[0]) == -1)
			ft_exit(data, lst_pid, NULL);
	}
}

void	ft_child(t_data *data, t_pid **lst_pid, int rd, int wr)
{
	if (data->nb_cmd == 2)
	{
		if (data->in == -1)
		{
			close(wr);
			close(rd);
			ft_exit(data, lst_pid, NULL);
		}
		if (dup2(data->in, STDIN_FILENO) == -1 || dup2(wr, STDOUT_FILENO) == -1)
			ft_exit(data, lst_pid, NULL);
	}
	else if (data->nb_cmd == data->ac - 2)
	{
		if (dup2(data->out, STDOUT_FILENO) == -1)
			ft_exit(data, lst_pid, NULL);
	}
	else if (dup2(wr, STDOUT_FILENO) == -1)
		ft_exit(data, lst_pid, NULL);
	if (close(rd) == -1 || close(wr) == -1)
		ft_exit(data, lst_pid, NULL);
	ft_access(data);
	if (!data->cmd_path)
	{
		errno = ENOENT;
		ft_exit(data, lst_pid, data->cmd_args[0]);
	}
	if (execve(data->cmd_path, data->cmd_args, data->env) == -1)
	{
		errno = ENOENT;
		ft_exit(data, lst_pid, data->cmd_args[0]);
	}
}

void	ft_access(t_data *data)
{
	int	i;

	i = -1;
	data->cmd_args = ft_split(data->av[data->nb_cmd], ' ');
	if (data->cmd_args == NULL)
		return ;
	if (access(data->cmd_args[0], X_OK) == 0)
	{
		data->cmd_path = data->cmd_args[0];
		return ;
	}
	data->cmd = ft_strjoin("/", data->cmd_args[0]);
	if (data->cmd == NULL)
		return ;
	while (data->path[++i])
	{
		data->cmd_path = ft_strjoin(data->path[i], data->cmd);
		if (!data->cmd_path)
			return ;
		if (access(data->cmd_path, X_OK) == 0)
			return ;
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	return ;
}

char	**ft_path(char **env)
{
	int	i;

	i = 0;
	if (!*env || !env)
	{
		return (NULL);
	}
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
	{
		i++;
	}
	if (!env[i])
	{
		return (NULL);
	}
	return (ft_split(env[i] + 5, ':'));
}
