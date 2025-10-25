/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:56:54 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 13:00:25 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Minimal Version */
void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	if (x >= 0 && x < img->w && y >= 0 && y < img->h)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int*)dst = color;
	}
}

void	ft_calculate_isos(t_fdf *fdf)
{
	int	x;
	int	y;
	double	angle;
	double	z;
	
	angle = fdf->data_cam->angle;
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			z = fdf->matrix[y][x].z * fdf->data_cam->z_scale;
			fdf->matrix[y][x].xiso = (x - y) * cos(angle) * fdf->data_cam->zoom + fdf->data_cam->x_off;
			fdf->matrix[y][x].yiso = ((x + y) * sin(angle) - z) * fdf->data_cam->zoom + fdf->data_cam->y_off;
			x++;
		}
		y++;
	}
}

// Dibuja un punto por cada nodo (para testing)
void ft_draw_map(t_fdf *fdf)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			ft_put_pixel(fdf->data_img, 
						fdf->matrix[y][x].xiso, 
						fdf->matrix[y][x].yiso, 
						0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->data_img->img, 0, 0);
}
