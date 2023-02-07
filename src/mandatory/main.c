/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 16:57:11 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	pid_t	first;

	if (ac != 5)
		return (ft_printf("Error\nExpected 4 arguments"), 1);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	ft_first(&data);
	first = data.pid;
	ft_last(&data);
	waitpid(first, NULL, 0);
	waitpid(data.pid, NULL, 0);
	return (0);
}
