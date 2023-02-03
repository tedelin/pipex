/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   little_pipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:21:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/03 16:03:22 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main(int ac, char **av, char **env)
{
	int	fd[2];
	int	p1;
	(void) ac;

	if (pipe(fd) == -1)
		return (1);
	p1 = fork();
	if (p1 == 0)// cmd2 wc
	{
		int out = open(av[4], O_WRONLY | O_CREAT);
		dup2(fd[0], STDIN_FILENO); // connect read side with stdin
		dup2(out, STDOUT_FILENO); // connect write side with file
		close(fd[0]);
		close(fd[1]);
		char **args = ft_split(av[3], ' ');
		execve("/bin/wc", args, env);
	}
	else // cmd1 grep
	{
		int	in = open(av[1], O_RDONLY);
		dup2(fd[1], STDOUT_FILENO); // connect write side to stdout
		dup2(in, STDIN_FILENO); // connect read side with stdin
		close(fd[0]);
		close(fd[1]);
		char **args2 = ft_split(av[2], ' ');
		execve("/bin/grep", args2, env);
	}
	return (0);
}
