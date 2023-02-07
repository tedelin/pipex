/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 12:24:51 by tedelin          ###   ########.fr       */
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
	t_data	data;

	if (ac != 5)
	 	return (ft_printf("Error\nExpected 4 arguments"), 1);
	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	ft_first(&data);
	ft_last(&data);
	return (0);
}
