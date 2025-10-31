/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:16:02 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/31 20:29:35 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Initialize principal struct */
void	ft_init(t_fdf *file_map)
{
	file_map->width = -1;
	file_map->height = 0;
	file_map->infile = 0;
	file_map->matrix = NULL;
	file_map->tokens = NULL;
	file_map->data_cam = NULL;
	file_map->data_img = NULL;
	file_map->mlx_ptr = NULL;
	file_map->win_ptr = NULL;
}

/* Initialize struct cam */
void	ft_init_cam(t_fdf *fdf)
{
	double	sx;
	double	sy;
	double	base;

	if (!fdf)
		return ;
	fdf->data_cam = malloc(sizeof(t_cam));
	if (!fdf->data_cam)
		ft_free_exit(fdf, "malloc cam failed\n", 1, 1);
	fdf->data_cam->angle = 0.523599;
	sx = (double)fdf->data_img->w / (fdf->width * 2.0);
	sy = (double)fdf->data_img->h / (fdf->height * 2.0);
	base = sx;
	if (sy < sx)
		base = sy;
	if (base < 1.0)
		base = 1.0;
	fdf->data_cam->zoom = base * 0.9;
	fdf->data_cam->z_scale = 2.5;
	fdf->data_cam->x_off = fdf->data_img->w / 2.0;
	fdf->data_cam->y_off = fdf->data_img->h * 0.2;
}

/* Initialize minilibx window and image */
int	ft_init_mlx(t_fdf *fdf)
{
	const int	win_w = 1280;
	const int	win_h = 720;

	fdf->mlx_ptr = mlx_init();
	if (fdf->mlx_ptr == NULL)
		return (1);
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, win_w, win_h, "FdF");
	if (fdf->win_ptr == NULL)
		return (1);
	fdf->data_img = malloc(sizeof(t_img));
	if (fdf->data_img == NULL)
		return (1);
	fdf->data_img->img = mlx_new_image(fdf->mlx_ptr, win_w, win_h);
	if (fdf->data_img->img == NULL)
		return (1);
	fdf->data_img->addr = mlx_get_data_addr (fdf->data_img->img,
			&fdf->data_img->bpp, &fdf->data_img->line_len,
			&fdf->data_img->endian);
	fdf->data_img->w = win_w;
	fdf->data_img->h = win_h;
	return (0);
}

/* MAIN FUNCTION */
int	main(int ac, char **av)
{
	t_fdf	fdf;
	char	*file_extension;

	if (ac != 2)
		ft_error("Not enough arguments or too much\n", 1);
	file_extension = ft_strrchr(av[1], '.');
	if (file_extension == NULL || ft_strncmp(file_extension, ".fdf", 4) != 0)
		ft_error("Not valid extension. Use: .fdf extension\n", 1);
	ft_init(&fdf);
	ft_validate_storage(av[1], &fdf);
	if (ft_init_mlx(&fdf) != 0)
		ft_free_exit(&fdf, "Error during initialization of mlx", 1, 1);
	ft_init_cam(&fdf);
	ft_calculate_isos(&fdf);
	ft_draw_map(&fdf);
	mlx_hook(fdf.win_ptr, 17, 0, ft_close, &fdf);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, ft_handle_keypress, &fdf);
	mlx_loop(fdf.mlx_ptr);
	ft_free_exit(&fdf, NULL, 0, 1);
	return (0);
}
