/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/07 17:04:08 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_data
{
	int		in;
	int		out;
	int		cmd;
	int		ac;
	pid_t	pid;
	char	**env;
	char	**path;
	char	**av;
}		t_data;

void	ft_first(t_data *data);
void	ft_last(t_data *data);

int		ft_exec(t_data *data, int nb);
char	**ft_path(char **env);
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char **tab);
void	ft_exit(void);

#endif
