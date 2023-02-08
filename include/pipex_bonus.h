/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/08 19:47:01 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
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
	int		nb_cmd;
	int		ac;
	pid_t	pid;
	char	*cmd_path;
	char	*cmd;
	char	**cmd_args;
	char	**env;
	char	**path;
	char	**av;
}		t_data;

void	ft_exec(t_data *data);
char	**ft_path(char **env);
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char **tab);
void	ft_exit(void);

void	ft_pipe(t_data *data, int rd, int wr);
void	ft_cmd(t_data *data, t_list **lst_pid);
void	ft_access(t_data *data);
void	ft_clear(t_data *data);

#endif
