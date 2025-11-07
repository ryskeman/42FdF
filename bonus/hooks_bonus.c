/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 20:04:49 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/07 19:35:01 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_handle_keypress(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
	{
		/*************DEBUGGING****************/
		ft_printf("REGISTRADO HOOK TECLADO (ESC)\n");
		/**************************************/
		ft_free_exit(fdf, NULL, 0, 0);
	}
	return (0);
}
