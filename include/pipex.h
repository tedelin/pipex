/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/04 19:49:46 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	int	in;
	int	out;
	char	**env;
	char	**path;
	char	**av;
}		t_data;

int		ft_exec(t_data *data, int nb);
char	**ft_path(char **env);
int		ft_process(t_data *data, int read, int write, int pid);
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char **tab);

#endif
