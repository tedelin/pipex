/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:14:40 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/24 17:03:12 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char	*ft_checkstash(char **stash)
{
	char	*line;
	int		i;

	if ((*stash) && ft_strchr((*stash), '\n'))
	{
		i = 0;
		line = malloc(sizeof(char) * (ft_alloc((*stash)) + 1));
		if (!line)
			return (NULL);
		while ((*stash)[i] && (*stash)[i] != '\n')
		{
			line[i] = (*stash)[i];
			i++;
		}
		line[i] = (*stash)[i];
		if ((*stash)[i] != '0')
			line[++i] = '\0';
		(*stash) = ft_strdupgnl(&(*stash)[i], (*stash));
		return (line);
	}
	return (NULL);
}

int	ft_read(int fd, char **buff)
{
	int	b_read;

	(*buff) = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buff))
		return (0);
	b_read = read(fd, (*buff), BUFFER_SIZE);
	if (b_read <= 0)
		return (free((*buff)), 0);
	(*buff)[b_read] = 0;
	return (b_read);
}

char	*ft_line(char **buff, char **stash)
{
	int		i;
	char	*line;

	if (!(*buff))
		return (free(*stash), NULL);
	i = 0;
	line = malloc(sizeof(char) * (ft_alloc((*buff)) + 1));
	if (!line)
		return (free(*buff), NULL);
	while ((*buff)[i] && (*buff)[i] != '\n')
	{
		line[i] = (*buff)[i];
		i++;
	}
	line[i] = (*buff)[i];
	if ((*buff)[i] != '\0')
		line[++i] = '\0';
	line = ft_strjoingnl((*stash), line);
	(*stash) = ft_strdupgnl(&(*buff)[i], (*buff));
	return (line);
}

char	*ft_lastline(char **stash)
{
	char	*line;

	line = ft_strdupgnl((*stash), (*stash));
	(*stash) = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buff;
	int			b_read;

	line = ft_checkstash(&stash);
	if (line)
		return (line);
	b_read = ft_read(fd, &buff);
	if (stash && b_read == 0 && !line)
		return (ft_lastline(&stash));
	if (!line && b_read > 0)
	{
		if (ft_strchr(buff, '\n'))
		{
			line = ft_line(&buff, &stash);
			if (!line)
				return (free(stash), NULL);
			return (line);
		}
		stash = ft_strjoingnl(stash, buff);
		return (get_next_line(fd));
	}
	return (NULL);
}
