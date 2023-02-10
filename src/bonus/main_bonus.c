/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/10 19:15:55 by tedelin          ###   ########.fr       */
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
	}
	while (pid)
	{
		tmp = pid;
		waitpid(pid->content, &data.status, 0);
		pid = pid->next;
		free(tmp);
	}
	free(pid);
	if (WIFEXITED(data.status))
		errno = WEXITSTATUS(data.status);
	ft_exit(&data, &pid, "main");
}
