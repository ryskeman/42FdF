/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:10:04 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/27 23:36:59 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Store data from file */
int	ft_store_data(t_fdf *file_map, int width, int row, char **tokens)
{
	int	col;

	col = 0;
	while (col < width)
	{
		file_map->matrix[row][col].x = col;
		file_map->matrix[row][col].y = row;
		if (!parse_token(&file_map->matrix[row][col], tokens[col]))
		 	return (0);
		col++;
	}
	return (1);
}

/* Aux process line */
int	ft_process_line_aux(int row, char **tokens, t_fdf *map, int mode)
{
	int	width;

	width = 0;
	while (tokens[width])
		width++;
	if (mode == 0)
	{
		if (map->width == -1)
			map->width = width;
		else if (width != map->width)
			return (0);
		map->height++;
		return (1);
	}
	else if (mode == 1)
	{
		if (!ft_store_data(map, width, row, tokens))
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

/* Process a line */
void	ft_process_line(char *line, t_fdf *fdf, int row, int mode)
{
	char	*trim_line;

	trim_line = ft_strtrim(line, " \t\n");
	if (!trim_line)
	{
		free(line);
		get_next_line(0, 1);
		ft_free_exit(fdf, "Memory error in trim\n", 1, 1);
	}
	fdf->tokens = ft_split(trim_line, ' ');
	if (!fdf->tokens || !ft_process_line_aux(row, fdf->tokens, fdf, mode))
	{
		free(trim_line);
		free(line);
		if (!fdf->tokens)
			ft_free_exit(fdf, "Memory error in split\n", 1, 1);
		get_next_line(0, 1);
		ft_free_exit(fdf, "Irregular map or invalid color/number\n", 1, 1);
	}
	ft_free_tokens(&fdf->tokens);
	free(trim_line);
}

/* Reading file */
void	ft_reading_file(t_fdf *file_map, int mode, int row)
{
	char	*line;

	while (1)
	{
		line = get_next_line(file_map->infile, 0);
		if (line != NULL)
		{
			if (line[0] != '\0' && line[0] != '\n')
			{
				ft_process_line(line, file_map, row, mode);
				if (mode == 1)
					row++;
				free(line);
			}
			else
			{
				free(line);
				get_next_line(0, 1);
				ft_free_exit(file_map, "Parsing error: Map invalid\n",
					1, 1);
			}
		}
		else
			break ;
	}
}

/* Read and store data from a file */
void	ft_validate_storage(char *filename, t_fdf *file_map)
{
	file_map->infile = open(filename, O_RDONLY);
	if (file_map->infile < 0)
		ft_free_exit(file_map, "Error opening file\n", 1, 1);
	ft_reading_file(file_map, 0, 0);
	ft_malloc_matrix(file_map);
	close(file_map->infile);
	file_map->infile = open(filename, O_RDONLY);
	if (file_map->infile < 0)
		ft_free_exit(file_map, "Error opening file\n", 1, 1);
	ft_reading_file(file_map, 1, 0);
}
// parsing_map.c - VERSIÓN MÍNIMA PARA TESTING
// void	ft_validate_storage(char *filename, t_fdf *fdf)
// {
//     char *line;
//     int y;    
//     // Abrir archivo
//     fdf->infile = open(filename, O_RDONLY);
//     if (fdf->infile < 0)
//         ft_free_exit(fdf, "Error: cannot open file\n", 1, 0);  
//     // Contar líneas y obtener width
//     fdf->height = 0;
//     while ((line = get_next_line(fdf->infile)))
//     {
//         fdf->tokens = ft_split(line, ' ');
//         if (fdf->width == -1)
//         {
//             fdf->width = 0;
//             while (fdf->tokens[fdf->width])
//                 fdf->width++;
//         }
//         fdf->height++;
//         ft_free_tokens(&fdf->tokens);
//         free(line);
//     }
//     close(fdf->infile);   
//     ft_printf("📊 Map dimensions: %dx%d\n", fdf->width, fdf->height);   
//     // Reservar memoria para matriz
//     fdf->matrix = malloc(sizeof(t_node *) * fdf->height);
//     if (!fdf->matrix)
//         ft_free_exit(fdf, "Error: malloc failed\n", 1, 0);  
//     // Reabrir para parsear
//     fdf->infile = open(filename, O_RDONLY);
//     y = 0;
//     while ((line = get_next_line(fdf->infile)))
//     {
//         fdf->matrix[y] = malloc(sizeof(t_node) * fdf->width);
//         if (!fdf->matrix[y])
//             ft_free_exit(fdf, "Error: malloc failed\n", 1, 0);
//         fdf->tokens = ft_split(line, ' ');
//         int x = 0;
//         while (fdf->tokens[x])
//         {
//             fdf->matrix[y][x].x = x;
//             fdf->matrix[y][x].y = y;
//             fdf->matrix[y][x].z = ft_atoi(fdf->tokens[x]);
//             fdf->matrix[y][x].color = 0xFFFFFF; // Blanco por defecto
//             x++;
//         }
//         ft_free_tokens(&fdf->tokens);
//         free(line);
//         y++;
//     }
//     close(fdf->infile);
//     fdf->infile = 0;    
//     ft_printf("✅ Map parsed successfully!\n");
// }
