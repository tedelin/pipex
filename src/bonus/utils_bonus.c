/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/09 15:10:18 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
