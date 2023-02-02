/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/02 18:41:29 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	main(int ac, char **av, char **env)
{
	char	**path;

	(void) av;
	if (ac != 5)
		return (ft_printf("Error\nExpected 4 arguments"), 1);
	path = ft_path(env);
	int	i = 0;
	if (!path)
		return (ft_printf("Error\nNo valid path found"), 2);
	char **cmd = ft_split(av[1], ' ');
	ft_exec(path, cmd[0], cmd, env);
}
