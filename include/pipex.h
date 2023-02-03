/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/03 16:03:22 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	int	in;
	int	out;
	// int cur_cmd // for bonus
	char	**env;
	char	**path;
	char	**av;
}		t_data;

int		ft_exec(char **path, char *comd, char **args, char **env);
char	**ft_path(char **env);
void	ft_child(t_data *data, int read, int write);
void	ft_parent(t_data *data, int read, int write);
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char **tab);

#endif
