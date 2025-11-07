/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:56:54 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/08 00:56:44 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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

	x = 0;
	while (x < fdf->height)
	{
		y = 0;
		while (y < fdf->width)
		{
			angle = (fdf->matrix[x][y].x - fdf->matrix[x][y].y)
				* cos(fdf->data_cam->angle) * fdf->data_cam->zoom;
			z = (fdf->matrix[x][y].x + fdf->matrix[x][y].y)
				* sin(fdf->data_cam->angle) * fdf->data_cam->zoom
				- (fdf->matrix[x][y].z * fdf->data_cam->z_scale);
			fdf->matrix[x][y].xiso = (int)angle + fdf->data_cam->x_off;
			fdf->matrix[x][y].yiso = (int)z + fdf->data_cam->y_off;
			y++;
		}
		x++;
	}
}

/* Drawing a map by nodes */
void	ft_draw_map(t_fdf *fdf)
{
	size_t	bytes;
	void	*mlx_ptr;
	void	*win_ptr;

	/*************DEBUGGING****************/
	ft_printf("ENTRA en ft_draw_map...\n");
	/**************************************/
	mlx_ptr = fdf->mlx_ptr;
	win_ptr = fdf->win_ptr;
	if (!fdf || !fdf->data_img)
		ft_free_exit(fdf, "Error rendering map\n", 1, 1);
	bytes = (size_t)fdf->data_img->line_len * (size_t)fdf->data_img->h;
	ft_bzero(fdf->data_img->addr, bytes);
	ft_draw_wireframe(fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->data_img->img, 0, 0);
	mlx_string_put(mlx_ptr, win_ptr, 50, 50, 0xFFFFFF, "FDF CONTROLS");
	mlx_string_put(mlx_ptr, win_ptr, 50, 80, 0xFFFFFF, "Move: W A S D");
	mlx_string_put(mlx_ptr, win_ptr, 50, 110, 0xFFFFFF, "Zoom: Scroll + -");
	mlx_string_put(mlx_ptr, win_ptr, 50, 140, 0xFFFFFF, "Exit: ESC");
	mlx_string_put(mlx_ptr, win_ptr, 50, 170, 0xFFFFFF, "Color controls: R G B N");
}

void	ft_draw_wireframe(t_fdf *fdf)
{
	int		x;
	int		y;

	/*************DEBUGGING****************/
	ft_printf("ENTRA en ft_draw_wireframe...\n");
	ft_printf("ANTES de ft_bresenham...\n");
	/**************************************/
	x = 0;
	while (x < fdf->height)
	{
		y = 0;
		while (y < fdf->width)
		{
			if (y + 1 < fdf->width)
				ft_bresenham(fdf->data_img, &fdf->matrix[x][y],
					&fdf->matrix[x][y + 1], fdf->data_cam->color_mode);
			if (x + 1 < fdf->height)
				ft_bresenham(fdf->data_img, &fdf->matrix[x][y],
					&fdf->matrix[x + 1][y], fdf->data_cam->color_mode);
			y++;
		}
		x++;
	}
	/*************DEBUGGING****************/
	ft_printf("DESPUES de ft_bresenham...\n");
	/**************************************/
}

/* Get color value based on z value */
int	ft_get_color_z(int z, t_fdf *fdf)
{
	double percent;

	if (fdf->z_max == fdf->z_min)
		return (0xFFFFFF);
	percent = (double)(z - fdf->z_min) / (double)(fdf->z_max - fdf->z_min);
	if (percent < 0.3)
		return (0x0000FF);
	else if (percent < 0.6)
		return (0x00FF00);
	else if (percent < 0.9)
		return (0x964B00);
	else
		return (0xFFFFFF);
}
