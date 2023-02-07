/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 13:52:39 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_list	*pid;
	t_list	*tmp;

	if (ac < 5)
		return (ft_printf("Error\nExpected at least 4 arguments"), 1);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	ft_first(&data, &pid);
	while (data.cmd < ac - 3)
		ft_middle(&data);
	ft_last(&data, &pid);
	while (pid)
	{
		tmp = pid;
		waitpid(pid->content, 0, NULL);
		pid = pid->next;
		free(tmp);
	}
	return (0);
}
