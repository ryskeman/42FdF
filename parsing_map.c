/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:10:04 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 12:56:15 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* TEMPORARY MINIMAL PARSING VERSION */
// void	ft_validate_storage(char *filename, t_fdf *file_map)
// {
// 	char	*line;
// 	int		y;

// 	file_map->infile = open(filename, O_RDONLY);
// 	if (file_map->infile < 0)
// 		ft_free_exit(file_map, "Error: cannot open file\n", 1, 0);
// 	file_map->height = 0;
// 	while ((line == get_next_line(file_map->infile)))
// 	{
// 		file_map->tokens = ft_split(line, ' ');
// 		if (file_map->width == -1)
// 		{
// 			file_map->width = 0;
// 			while (file_map->tokens[file_map->width])
// 				file_map->width++;
// 		}
// 		file_map->height++;
// 		ft_free_tokens(&file_map->tokens);
// 		free(line);
// 	}
// 	if (file_map->infile > 0)
// 		close(file_map->infile);
// }

// parsing_map.c - VERSIÓN MÍNIMA PARA TESTING
void	ft_validate_storage(char *filename, t_fdf *fdf)
{
    char *line;
    int y;
    
    // Abrir archivo
    fdf->infile = open(filename, O_RDONLY);
    if (fdf->infile < 0)
        ft_free_exit(fdf, "Error: cannot open file\n", 1, 0);
    
    // Contar líneas y obtener width
    fdf->height = 0;
    while ((line = get_next_line(fdf->infile)))
    {
        fdf->tokens = ft_split(line, ' ');
        if (fdf->width == -1)
        {
            fdf->width = 0;
            while (fdf->tokens[fdf->width])
                fdf->width++;
        }
        fdf->height++;
        ft_free_tokens(&fdf->tokens);
        free(line);
    }
    close(fdf->infile);
    
    ft_printf("📊 Map dimensions: %dx%d\n", fdf->width, fdf->height);
    
    // Reservar memoria para matriz
    fdf->matrix = malloc(sizeof(t_node *) * fdf->height);
    if (!fdf->matrix)
        ft_free_exit(fdf, "Error: malloc failed\n", 1, 0);
    
    // Reabrir para parsear
    fdf->infile = open(filename, O_RDONLY);
    y = 0;
    while ((line = get_next_line(fdf->infile)))
    {
        fdf->matrix[y] = malloc(sizeof(t_node) * fdf->width);
        if (!fdf->matrix[y])
            ft_free_exit(fdf, "Error: malloc failed\n", 1, 0);
        
        fdf->tokens = ft_split(line, ' ');
        int x = 0;
        while (fdf->tokens[x])
        {
            fdf->matrix[y][x].x = x;
            fdf->matrix[y][x].y = y;
            fdf->matrix[y][x].z = ft_atoi(fdf->tokens[x]);
            fdf->matrix[y][x].color = 0xFFFFFF; // Blanco por defecto
            x++;
        }
        ft_free_tokens(&fdf->tokens);
        free(line);
        y++;
    }
    close(fdf->infile);
    fdf->infile = 0;
    
    ft_printf("✅ Map parsed successfully!\n");
}
