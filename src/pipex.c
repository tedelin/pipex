/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:40:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/02 18:42:11 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	ft_exec(char **path, char *comd, char **args, char **env)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_strjoin("/", comd);
	if (!cmd)
		return (1);
	while (path[i])
	{
		cmd = ft_strjoin(path[i], cmd);
		if (!cmd)
			return (1); // protect but still to free previous malloc
		if (access(cmd, X_OK) == 0)
		{
			execve(cmd, args, env);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_path(char **env)
{
	char	*path;
	int		i;

	if (!*env || !env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		path = ft_strnstr(env[i], "PATH=", 5);
		if (path)
		{
			path += 5;
			break;
		}
		i++;
	}
	return (ft_split(path, ':'));
}
