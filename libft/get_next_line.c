/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 19:26:41 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 11:56:27 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
