/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:10:04 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 12:44:10 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* TEMPORARY MINIMAL PARSING VERSION */
void	ft_validate_storage(char *filename, t_fdf *file_map)
{
	char	*line;
	int		y;

	file_map->infile = open(filename, O_RDONLY);
	if (file_map->infile < 0)
		ft_free_exit(file_map, "Error: cannot open file\n", 1, 0);
	file_map->height = 0;
	while ((line == get_next_line(file_map->infile)))
	{
		file_map->tokens = ft_split(line, ' ');
		if (file_map->width == -1)
		{
			file_map->width = 0;
			while (file_map->tokens[file_map->width])
				file_map->width++;
		}
		file_map->height++;
		ft_free_tokens(&file_map->tokens);
		free(line);
	}
	if (file_map->infile > 0)
		close(file_map->infile);
}
