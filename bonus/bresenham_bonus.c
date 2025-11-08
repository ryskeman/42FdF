/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:41:09 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/08 14:49:06 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Initialize bresenham algorithm */
void	ft_init_bresenham(t_bresenham *b, t_node *a, t_node *b_node)
{
	int	dx_val;
	int	dy_val;

	dx_val = b_node->xiso - a->xiso;
	dy_val = b_node->yiso - a->yiso;
	b->dx = abs(dx_val);
	b->dy = abs(dy_val);
	b->sx = 1;
	if (dx_val < 0)
		b->sx = -1;
	b->sy = 1;
	if (dy_val < 0)
		b->sy = -1;
	b->err = b->dx - b->dy;
}

/* Apply Bresenham algorithm to draw lines */
void	ft_bresenham(t_img *img, t_node *a, t_node *b, int color_mode)
{
	t_bresenham	b_data;
	t_color		conf;

	ft_init_bresenham(&b_data, a, b);
	b_data.x_c = a->xiso;
	b_data.y_c = a->yiso;
	conf.color_mode = color_mode;
	while (1)
	{
		ft_color_config(a, b, &conf, &b_data);
		ft_put_pixel (img, b_data.x_c, b_data.y_c, ft_get_color(&conf));
		if (b_data.x_c == b->xiso && b_data.y_c == b->yiso)
			break ;
		b_data.e2val = 2 * b_data.err;
		if (b_data.e2val > -b_data.dy)
		{
			b_data.err -= b_data.dy;
			b_data.x_c += b_data.sx;
		}
		if (b_data.e2val < b_data.dx)
		{
			b_data.err += b_data.dx;
			b_data.y_c += b_data.sy;
		}
	}
}

/* Assign node color by z values */
void	ft_assign_z(t_fdf *fdf)
{
	int		i;
	int		j;
	t_node	*node;

	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (j < fdf->width)
		{
			node = &fdf->matrix[i][j];
			if (node->color == -1)
				node->color = ft_get_color_z(node->z, fdf);
			j++;
		}
		i++;
	}
}
