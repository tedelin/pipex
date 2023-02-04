/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:40:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/04 14:08:50 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int	ft_process(t_data *data, int read, int write, int pid)
{
	static int	nb = 0;

	if (data->in == -1 && pid != 0)
		data->in = open("/dev/null", O_RDONLY);
	if (pid != 0)
	{
		if (nb == 0)
			nb = 2;
		if (dup2(write, STDOUT_FILENO) == -1 || dup2(data->in, STDIN_FILENO) == -1)
			return (perror(" "), exit(errno), errno);
	}
	else if (pid == 0)
	{
		if (nb == 0)
			nb = 3;
		if (dup2(read, STDIN_FILENO) == -1 || dup2(data->out, STDOUT_FILENO) == -1)
			return (perror(" "), exit(errno), errno);
	}
	close(read);
	close(write);
	if (ft_exec(data, nb++) == 1)
		return (perror("execve command not found"), exit(errno), 127);
	return (0);
}
