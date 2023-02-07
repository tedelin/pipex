/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 16:42:59 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_list	*pid;
	t_list	*tmp;

	if (ac < 5)
		return (ft_printf("Error : Expected at least 4 arguments\n"), 1);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	pid = NULL;
	while (data.cmd < ac - 2)
		ft_cmd(&data, &pid);
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
	return (0);
}
