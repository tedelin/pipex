/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/08 00:32:57 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_exec(t_data *data)
{
	int		i;
	char	*cmd;
	char	*path_cmd;
	char	**args;

	i = -1;
	args = ft_split(data->av[data->cmd], ' ');
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
	return (free_split(args), 1);
}

char	**ft_path(char **env)
{
	int		i;

	if (!*env || !env)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			return (ft_split(env[i] + 5, ':'));
		}
	}
	return (NULL);
}

void	init_data(t_data *data, int ac, char **av, char **env)
{
	data->path = ft_path(env);
	if (!data->path)
	{
		ft_putendl_fd("Error while trying to find path", 2);
		exit(1);
	}
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->cmd = 1;
	data->in = open(av[1], O_RDONLY);
	data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (data->out == -1)
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

void	ft_exit(void)
{
	perror("Error ");
	exit(errno);
}
