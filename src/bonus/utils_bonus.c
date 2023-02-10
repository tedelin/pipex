/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/10 11:42:51 by tedelin          ###   ########.fr       */
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

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_exit(t_data *data, t_pid **lst_pid, char *msg)
{
	t_pid	*tmp;

	if (!msg && errno != 0)
		perror("Error ");
	else if (ft_strncmp(msg, "main", 4) != 0 && errno != 0)
		perror(msg);
	while ((*lst_pid))
	{
		tmp = (*lst_pid);
		(*lst_pid) = (*lst_pid)->next;
		free(tmp);
	}
	free((*lst_pid));
	free_split(data->cmd_args);
	free_split(data->path);
	free(data->cmd);
	free(data->cmd_path);
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
	exit(errno);
}
