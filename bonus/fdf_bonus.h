/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:52:43 by fernafer          #+#    #+#             */
/*   Updated: 2025/11/08 11:02:59 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

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
	int			color_mode;
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
	int			z_min;
	int			z_max;
	t_node		**matrix;
	t_cam		*data_cam;
	t_img		*data_img;
	char		**tokens;
	void		*mlx_ptr;
	void		*win_ptr;
}			t_fdf;

/* Bresenham struct */
typedef struct s_bresenham
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			e2val;
	int			x_c;
	int			y_c;
}			t_bresenham;

/* Store data to set color */
typedef struct s_color
{
	t_node		*a;
	t_node		*b;
	int			x;
	int			y;
	int			color_mode;
	double		r_f;
	double		g_f;
	double		b_f;
	int			r;
	int			g;
	int			b_;
}			t_color;

/* cleanup_bonus.c */
int				ft_close(t_fdf *fdf);
void			ft_error(char *msg, int exit_code);
void			ft_free_exit(t_fdf *fdf, char *msg, int exit_code,
					int from_my_code);
void			ft_free_tokens(char ***tokens_ptr);
void			ft_free_matrix(t_node **nodes, int height);

/* main_bonus.c */
void			ft_init(t_fdf *file_map);
void			ft_init_cam(t_fdf *fdf);
int				ft_init_mlx(t_fdf *fdf);
int				main(int ac, char **av);

/* parsing_map_bonus.c */
int				ft_store_data(t_fdf *file_map, int width, int row,
					char **tokens);
int				ft_process_line_aux(int row, char **tokens, t_fdf *map,
					int mode);
void			ft_process_line(char *line, t_fdf *fdf, int row,
					int mode);
void			ft_reading_file(t_fdf *file_map, int mode, int row);
void			ft_validate_storage(char *filename, t_fdf *file_map);

/* draw_bonus.c */
void			ft_put_pixel(t_img *img, int x, int y, int color);
void			ft_calculate_isos(t_fdf *fdf);
void			ft_draw_map(t_fdf *fdf);
void			ft_draw_wireframe(t_fdf *fdf);
int				ft_get_color_z(int z, t_fdf *fdf);

/* hooks_bonus.c */
int				ft_handle_keypress(int keycode, t_fdf *fdf);
int				ft_handle_zoom(int keycode, int x, int y, void *param);

/* bresenham_bonus.c */
void			ft_init_bresenham(t_bresenham *b, t_node *a, t_node *b_node);
void			ft_bresenham(t_img *img, t_node *a, t_node *b, int color_mode);
void			ft_assign_z(t_fdf *fdf);

/* utils_bonus.c */
int				parse_token(t_node *node, char *token);
int				is_valid_hexa(const char *str);
void			ft_malloc_matrix(t_fdf *file_map);

/* colors_bonus.c */
void			ft_find_z_minmax(t_fdf *fdf);
void			ft_color_config(t_node *a, t_node *b, t_color *conf,
					t_bresenham *b_data);
double			ft_get_percent(int start, int end, int current);
int				ft_interpolate(int start, int end, double t);
int				ft_get_color(t_color *conf);

#endif