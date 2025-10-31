/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:56:54 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/31 20:31:50 by fernafer         ###   ########.fr       */
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
	bytes = (size_t)fdf->data_img->line_len
		* (size_t)fdf->data_img->h;
	ft_bzero(fdf->data_img->addr, bytes);
	ft_draw_wireframe(fdf);
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
			if (x < fdf->width - 1)
				ft_bresenham(fdf->data_img, &fdf->matrix[x][y],
					&fdf->matrix[x][y + 1]);
			if (y < fdf->height - 1)
				ft_bresenham(fdf->data_img, &fdf->matrix[x][y],
					&fdf->matrix[x + 1][y]);
			x++;
		}
		y++;
	}
}
