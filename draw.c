/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:56:54 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/30 00:00:45 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Put pixel in mlx img */
void	ft_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || x >= img->w || y < 0 || y >= img->h)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	ft_calculate_isos(t_fdf *fdf)
{
	int		x;
	int		y;
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
			fdf->matrix[y][x].xiso = (int)((x - y) * cos(angle)
					* fdf->data_cam->zoom) + fdf->data_cam->x_off;
			fdf->matrix[y][x].yiso = (int)((x + y) * sin(angle)
					* fdf->data_cam->zoom - z) + fdf->data_cam->y_off;
			x++;
		}
		y++;
	}
}

/* Drawing a map by nodes */
void	ft_draw_map(t_fdf *fdf)
{
	size_t	bytes;

	if (!fdf || !fdf->data_img)
		ft_free_exit(fdf, "Error rendering map\n", 1, 1);
	/* Cleaning image */
	bytes = (size_t)fdf->data_img->line_len
		* (size_t)fdf->data_img->h;
	ft_bzero(fdf->data_img->addr, bytes);
	/* Drawing wireframe */
	ft_draw_wireframe(fdf);
	/* Show image to window/screen */
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr,
		fdf->data_img->img, 0, 0);
}

void	ft_draw_wireframe(t_fdf *fdf)
{
	int		x;
	int		y;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			// Conect with rigth node
			if (x < fdf->width - 1)
				/* DRAW BRESENHAM */
			// Conect with belows node
			if (y < fdf->height - 1)
				/* DRAW BRESENHAM */
			x++;
		}
		y++;
	}
}
