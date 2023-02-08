/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/08 19:42:03 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_list	*pid;
	t_list	*tmp;

	init_data(&data, ac, av, env);
	pid = NULL;
	while (data.nb_cmd < ac - 2)
	{
		ft_cmd(&data, &pid);
		ft_clear(&data);
	}
	while (pid)
	{
		tmp = pid;
		waitpid(*((pid_t *)pid->content), NULL, 0);
		pid = pid->next;
		free(tmp);
	}
	close(data.in);
	close(data.out);
	free_split(data.path);
	exit(errno);
}
