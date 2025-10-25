/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:26:41 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 15:00:26 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_two(char **ptr1, char **ptr2)
{
	if (ptr1 && *ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2 && *ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (NULL);
}

static char	*ft_get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

static void	ft_update_stash(char **stash)
{
	int		i;
	char	*new_stash;

	if (!stash || !*stash)
		return ;
	i = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if (!((*stash)[i]))
	{
		free(*stash);
		*stash = NULL;
	}
	else
	{
		new_stash = ft_strdup(*stash + i + 1);
		free(*stash);
		*stash = new_stash;
	}
}

static int	ft_read(int fd, char **stash, char **buffer)
{
	int		bytes_read;
	char	*tmp;

	if (!*stash)
		*stash = ft_strdup("");
	while (!ft_strchr(*stash, '\n'))
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (0);
		if (bytes_read == 0)
			break ;
		(*buffer)[bytes_read] = '\0';
		tmp = ft_strjoin(*stash, *buffer);
		if (!tmp)
			return (0);
		free(*stash);
		*stash = tmp;
	}
	return (1);
}

char	*get_next_line(int fd, int flush)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (flush)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free_two(&stash, &buffer));
	if (!ft_read(fd, &stash, &buffer))
		return (free_two(&stash, &buffer));
	line = ft_get_line(stash);
	if (!line || line[0] == '\0')
		return (free(line), free_two(&stash, &buffer));
	ft_update_stash(&stash);
	free(buffer);
	return (line);
}
/**
 * static char *stash;

char	**get_stash_ptr(void)
{
	return (&stash);
}

void	free_stash(void)
{
	if (stash)
	{
		free(stash);
		stash = NULL;
	}
}
*/
/* Original function GNL belows */
/* 
static char	*ft_free(char *tmp)
{
	if (tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

static char	*ft_reading(int fd, char *buffer)
{
	char		*tmp;
	ssize_t		readed;

	if (!buffer)
		buffer = ft_strdup("");
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (ft_free(buffer));
	while (buffer && !ft_strchr(buffer, '\n'))
	{
		readed = read(fd, tmp, BUFFER_SIZE);
		if (readed < 0)
			return (ft_free(buffer), ft_free(tmp));
		if (readed == 0)
		{
			if (buffer[0] == '\0')
				return (ft_free(tmp), buffer);
			break ;
		}
		tmp[readed] = '\0';
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (ft_free(buffer));
	}
	return (ft_free(tmp), buffer);
}

static char	*ft_nl(char **buffer)
{
	char	*line;
	char	*newline;
	char	*remaining;

	if (!buffer || !*buffer)
		return (NULL);
	newline = ft_strchr(*buffer, '\n');
	if (newline)
	{
		line = ft_substr(*buffer, 0, newline - *buffer + 1);
		remaining = ft_strdup(newline + 1);
		free(*buffer);
		*buffer = remaining;
		if (!line)
			return (ft_free(line));
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffers[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffers[fd] = ft_reading(fd, buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = ft_nl(&buffers[fd]);
	if (line && line[0] == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}
*/
