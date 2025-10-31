/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:41:09 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/31 20:27:31 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		b->sy = -1;
	b->err = b->dx - b->dy;
}

/* Apply Bresenham algorithm to draw lines */
void	ft_bresenham(t_img *img, t_node *a, t_node *b)
{
	t_bresenham	b_data;
	int			e2_val;
	int			x_current;
	int			y_current;

	ft_init_bresenham(&b_data, a, b);
	x_current = a->xiso;
	y_current = a->yiso;
	while (1)
	{
		ft_put_pixel (img, x_current, y_current, a->color);
		if (x_current == b->xiso && y_current == b->yiso)
			break ;
		e2_val = 2 * b_data.err;
		if (e2_val > -b_data.dy)
		{
			b_data.err -= b_data.dy;
			x_current += b_data.sx;
		}
		if (e2_val < b_data.dx)
		{
			b_data.err += b_data.dx;
			y_current += b_data.sy;
		}
	}
}
