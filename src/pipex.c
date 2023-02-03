/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:40:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/03 18:17:49 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	ft_exec(char **path, char *comd, char **args, char **env)
{
	int		i;
	char	*cmd;

	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], comd);
		if (!cmd)
			return (1);
		if (access(cmd, X_OK) == 0)
		{
			if (execve(cmd, args, env) == -1)
				return (perror(strerror(errno)), 1);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_path(char **env)
{
	char	*path;
	int		i;

	if (!*env || !env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			path = env[i];
			path += 5;
			break ;
		}
		i++;
	}
	return (ft_split(path, ':'));
}

void	ft_child(t_data *data, int read, int write)
{
	char	**args;
	char	*cmd;

	if (dup2(read, STDIN_FILENO) == -1 || dup2(data->out, STDOUT_FILENO) == -1)
	{
		perror("Error ");
		// exit(errno);
	}
	close(read);
	close(write);
	args = ft_split(data->av[3], ' ');
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free_split(args);
		return ;
	}
	ft_exec(data->path, cmd, args, data->env);
	free_split(args);
	free(cmd);
}

// if no such file or directory and cmd X_OK -> execute without error msg
// else if no such file or directory and cmd X_KO -> error no such file or directory

void	ft_parent(t_data *data, int read, int write)
{
	char	**args;
	char	*cmd;

	if (dup2(write, STDOUT_FILENO) == -1 || dup2(data->in, STDIN_FILENO) == -1) // force to fail if fd == -1
	{
		perror("Error ");
		exit(errno);
	}
	close(read);
	close(write);
	args = ft_split(data->av[2], ' ');
	cmd = ft_strjoin("/", args[0]);
	if (!cmd)
	{
		free_split(args);
		return ;
	}
	if (ft_exec(data->path, cmd, args, data->env) == 1)
	{
		perror("Error ");
		exit(errno);
	}
	free_split(args);
	free(cmd);
}

void	init_data(t_data *data, int ac, char **av, char **env)
{
	data->path = ft_path(env);
	if (!data->path)
		exit(errno);
	data->env = env;
	data->av = av;
	data->in = open(av[1], O_RDONLY);
	data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
}
