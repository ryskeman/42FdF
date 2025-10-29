/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:41:09 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/30 00:03:58 by fernafer         ###   ########.fr       */
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
	/* APPLY BRESENHAM HERE */
}
