/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/09 17:33:58 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_pid	*pid;
	t_pid	*tmp;

	init_data(&data, ac, av, env);
	pid = NULL;
	while (++data.nb_cmd <= ac - 2)
	{
		ft_process(&data, &pid);
		ft_clear(&data);
	}
	while (pid)
	{
		tmp = pid;
		waitpid(pid->content, &data.status, 0);
		pid = pid->next;
		free(tmp);
	}
	close(data.in);
	close(data.out);
	free_split(data.path);
	if (WIFEXITED(data.status))
		exit(WEXITSTATUS(data.status));
	else
		exit(0);
}
