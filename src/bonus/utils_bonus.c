/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/08 19:47:18 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	init_data(t_data *data, int ac, char **av, char **env)
{
	if (ac < 5)
	{
		ft_putendl_fd("Error : Expected at least 4 arguments", 2);
		exit(1);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->path = ft_path(env);
	if (!data->path)
	{
		ft_putendl_fd("Error while trying to find path", 2);
		exit(1);
	}
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->nb_cmd = 1;
	data->in = open(av[1], O_RDONLY);
	data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0777);
	if (data->out == -1)
	{
		perror("File Error ");
		exit(errno);
	}
}

void	ft_clear(t_data *data)
{
	free_split(data->cmd_args);
	free(data->cmd);
	free(data->cmd_path);
	data->cmd_args = NULL;
	data->cmd = NULL;
	data->cmd_path = NULL;
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

// int	ft_exec(t_data *data)
// {
// 	int		i;
// 	char	*cmd;
// 	char	*path_cmd;
// 	char	**args;

// 	i = -1;
// 	args = ft_split(data->av[data->cmd], ' ');
// 	if (args == NULL)
// 		return (free_split(args), 1);
// 	cmd = ft_strjoin("/", args[0]);
// 	if (cmd == NULL)
// 		return (free_split(args), 1);
// 	while (data->path[++i])
// 	{
// 		path_cmd = ft_strjoin(data->path[i], cmd);
// 		if (!path_cmd)
// 			return (free_split(args), 1);
// 		if (access(path_cmd, X_OK) == 0)
// 		{
// 			if (execve(path_cmd, args, data->env) == -1)
// 				return (free(path_cmd), free_split(args), 1);			
// 		}
// 		free(path_cmd);
// 	}
// 	return (free_split(args), 1);
// }
