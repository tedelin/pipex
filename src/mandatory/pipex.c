/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 12:36:37 by tedelin          ###   ########.fr       */
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

void ft_first(t_data *data)
{
    int fd[2];
    int   pid;

    if (pipe(fd) == -1)
    {
        perror("Pipe ");
        exit(errno);
    }
    pid = fork();
    if (pid == 0)
    {
        dup2(data->in, STDIN_FILENO);
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        ft_exec(data, 2);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        wait(NULL);
    }
}

void ft_last(t_data *data)
{
    int fd[2];
    int   pid;

    if (pipe(fd) == -1)
    {
        perror("Pipe ");
        exit(errno);
    }
    pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        dup2(data->out, STDOUT_FILENO);
        close(fd[1]);
        ft_exec(data, 3);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        wait(NULL);
    }
}
