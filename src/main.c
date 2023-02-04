/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/04 13:58:26 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	int		pid;
	t_data	data;

	if (ac != 5)
	 	return (ft_printf("Error\nExpected 4 arguments"), 1);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	if (pipe(fd) == -1)
	{
		perror("Error ");
		return (errno);
	}
	pid = fork();
	if (pid == 0)
	{
		ft_process(&data, fd[0], fd[1], pid);
	}
	else
	{
		ft_process(&data, fd[0], fd[1], pid);
	}
	return (0);
}
