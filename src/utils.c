/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/04 17:20:06 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int	ft_exec(t_data *data, int nb)
{
	int		i;
	char	*cmd;
    char	*path_cmd;
    char	**args;

	i = -1;
    args = ft_split(data->av[nb], ' ');
    if (args == NULL)
		return (free_split(args), 1);
	cmd = ft_strjoin("/", args[0]);
    if (cmd == NULL)
		return (free_split(args), 1);
	while (data->path[++i])
	{
		path_cmd = ft_strjoin(data->path[i], cmd);
		if (!path_cmd)
			return (free_split(args), 1);
		if (access(path_cmd, X_OK) == 0)
		{
			if (execve(path_cmd, args, data->env) == -1)
				return (free(path_cmd), free_split(args), 1);
			return (free(path_cmd), free_split(args), 0);
		}
        free(path_cmd);
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

void	init_data(t_data *data, int ac, char **av, char **env)
{
	data->path = ft_path(env);
	if (!data->path)
		exit(errno);
	data->env = env;
	data->av = av;
	data->in = open(av[1], O_RDONLY);
	data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (data->out == -1) // data->in == - 1 || 
		perror("File Error ");
}

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}
