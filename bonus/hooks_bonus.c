/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:04:49 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/08 11:02:07 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_handle_keypress(int keycode, t_fdf *fdf)
{
	int	sptep;

	sptep = 10;
	if (keycode == 65307)
		ft_free_exit(fdf, NULL, 0, 0);
	else if (keycode == 119)
		fdf->data_cam->y_off += sptep;
	else if (keycode == 115)
		fdf->data_cam->y_off -= sptep;
	else if (keycode == 97)
		fdf->data_cam->x_off += sptep;
	else if (keycode == 100)
		fdf->data_cam->x_off -= sptep;
	else if (keycode == 114)
		fdf->data_cam->color_mode = 1;
	else if (keycode == 103)
		fdf->data_cam->color_mode = 2;
	else if (keycode == 98)
		fdf->data_cam->color_mode = 3;
	else if (keycode == 110)
		fdf->data_cam->color_mode = 0;
	ft_calculate_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}

/* Zoom hooks */
int	ft_handle_zoom(int keycode, int x, int y, void *param)
{
	t_fdf	*fdf;
	double	prev_zoom;
	double	scale;

	fdf = (t_fdf *)param;
	prev_zoom = fdf->data_cam->zoom;
	if (keycode == 4)
		fdf->data_cam->zoom *= 1.1;
	else if (keycode == 5)
	{
		fdf->data_cam->zoom /= 1.1;
		if (fdf->data_cam->zoom < 0.1)
			fdf->data_cam->zoom = 0.1;
	}
	else
		return (0);
	scale = fdf->data_cam->zoom / prev_zoom;
	fdf->data_cam->x_off = x - scale * (x - fdf->data_cam->x_off);
	fdf->data_cam->y_off = y - scale * (y - fdf->data_cam->y_off);
	ft_calculate_isos(fdf);
	ft_draw_map(fdf);
	return (0);
}
