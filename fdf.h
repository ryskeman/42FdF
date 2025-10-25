/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:52:43 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/25 16:42:09 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h> // open
# include <math.h>  // cos & sin
# include <stdlib.h>

/* STRUCTS DECLARATION */
/* Data points (Using matrix) */
typedef struct s_node
{
	int		color;
	int		x;
	int		y;
	int		z;
	int		xiso;
	int		yiso;
}			t_node;

/* Camera params */
typedef struct s_cam
{
	double		zoom;
	double		z_scale;
	double		angle;
	double		x_off;
	double		y_off;
}			t_cam;

/* Image buffer */
typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}			t_img;

/* Main struct */
typedef struct s_fdf
{
	int			width;
	int			height;
	int			infile;
	t_node		**matrix;
	t_cam		*data_cam;
	t_img		*data_img;
	char		**tokens;
	void		*mlx_ptr;
	void		*win_ptr;
}			t_fdf;

/* cleanup.c */
int				ft_close(t_fdf *fdf);
void			ft_error(char *msg, int exit_code);
void			ft_free_exit(t_fdf *fdf, char *msg, int exit_code,
					int from_my_code);
void			ft_free_tokens(char ***tokens_ptr);
void			ft_free_matrix(t_node **nodes, int height);

/* main.c */
void			ft_init(t_fdf *file_map);
void			ft_init_cam(t_fdf *fdf);
int				ft_init_mlx(t_fdf *fdf);
int				main(int ac, char **av);

/* parsing_map.c */
int				ft_store_data(t_fdf *file_map, int width, int row,
					char **tokens);
int				ft_process_line_aux(int row, char **tokens, t_fdf *map,
					int mode);
void			ft_process_line(char *line, t_fdf *fdf, int row,
					int mode);
void			ft_reading_file(t_fdf *file_map, int mode, int row);
void			ft_validate_storage(char *filename, t_fdf *file_map);

/* draw.c */
void			ft_put_pixel(t_img *img, int x, int y, int color);
void			ft_calculate_isos(t_fdf *fdf);
void			ft_draw_map(t_fdf *fdf);

/* bresenham .c */
/* utils.c */

#endif