/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:46:38 by fernando          #+#    #+#             */
/*   Updated: 2025/11/07 19:34:40 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

/* Close function using X symbol */
int	ft_close(t_fdf *fdf)
{
	/*************DEBUGGING****************/
	ft_printf("Cerrando ventana...\n");
	/**************************************/
	ft_free_exit(fdf, NULL, 0, 1);
	return (0);
}

/* Prints error message */
void	ft_error(char *msg, int exit_code)
{
	if (msg)
		ft_printf("\033[0;31m%s\033[0m", msg);
	exit(exit_code);
}

/* Handle error, free and exit */
void	ft_free_exit(t_fdf *fdf, char *msg, int exit_code, int from_my_code)
{
	if (fdf->tokens)
		ft_free_tokens(&fdf->tokens);
	if (fdf->matrix)
		ft_free_matrix(fdf->matrix, fdf->height);
	if (fdf->infile > 0)
		close(fdf->infile);
	if (fdf->data_img)
	{
		if (fdf->data_img->img)
			mlx_destroy_image(fdf->mlx_ptr, fdf->data_img->img);
	}
	if (from_my_code && fdf->win_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	ft_error(msg, exit_code);
}

void	ft_free_tokens(char ***tokens_ptr)
{
	int		i;
	char	**tokens;

	if (!tokens_ptr || !*tokens_ptr)
		return ;
	tokens = *tokens_ptr;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
	*tokens_ptr = NULL;
}

/* Free the nodes and matrix */
void	ft_free_matrix(t_node **nodes, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(nodes[i]);
		i++;
	}
	free(nodes);
}
