/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 20:39:39 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/08 15:33:16 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Set up color struct */
void	ft_color_config(t_node *a, t_node *b, t_color *conf,
			t_bresenham *b_data)
{
	conf->a = a;
	conf->b = b;
	conf->x = b_data->x_c;
	conf->y = b_data->y_c;
	conf->r_f = 1.0;
	conf->g_f = 1.0;
	conf->b_f = 1.0;
	conf->r = 0;
	conf->g = 0;
	conf->b_ = 0;
}

/* Find z min and max values */
void	ft_find_z_minmax(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			if (fdf->matrix[i][j].z < fdf->z_min)
				fdf->z_min = fdf->matrix[i][j].z;
			if (fdf->matrix[i][j].z > fdf->z_max)
				fdf->z_max = fdf->matrix[i][j].z;
			j++;
		}
		i++;
	}
}

/* Get the percentage to calculate color */
double	ft_get_percent(int start, int end, int current)
{
	if (start == end)
		return (1.0);
	return ((double)(current - start) / (double)(end - start));
}

/* Interpolate values */
int	ft_interpolate(int start, int end, double t)
{
	return ((int)(start + (end - start) * t));
}

/* Get color to draw */
int	ft_get_color(t_color *conf)
{
	double	percent;

	if (conf->a->color == 0x000000 && conf->b->color == 0x000000)
		return (0xFFFFFF);
	if (abs(conf->b->xiso - conf->a->xiso) > abs(conf->b->yiso - conf->a->yiso))
		percent = ft_get_percent(conf->a->xiso, conf->b->xiso, conf->x);
	else
		percent = ft_get_percent(conf->a->yiso, conf->b->yiso, conf->y);
	conf->r = ft_interpolate(((conf->a->color >> 16) & 0xFF),
			((conf->b->color >> 16) & 0xFF), percent);
	conf->g = ft_interpolate(((conf->a->color >> 8) & 0xFF),
			((conf->b->color >> 8) & 0xFF), percent);
	conf->b_ = ft_interpolate((conf->a->color & 0xFF), (conf->b->color & 0xFF),
			percent);
	if (conf->color_mode == 1)
		conf->r_f = 1.5;
	else if (conf->color_mode == 2)
		conf->g_f = 1.5;
	else if (conf->color_mode == 3)
		conf->b_f = 1.5;
	conf->r = fmin(255, (int)(conf->r * conf->r_f));
	conf->g = fmin(255, (int)(conf->g * conf->g_f));
	conf->b_ = fmin(255, (int)(conf->b_ * conf->b_f));
	return ((conf->r << 16) | (conf->g << 8) | conf->b_);
}
