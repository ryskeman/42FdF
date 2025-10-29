/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:38:32 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/29 23:33:19 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Validates z value and color value */
int	parse_token(t_node *node, char *token)
{
	char	*comma;
	int		value;

	comma = ft_strchr(token, ',');
	if (comma)
	{
		*comma = '\0';
		if (ft_safe_atoi(token, &value) == 0)
			return (0);
		node->z = value;
		if (!is_valid_hexa(comma + 1))
			return (0);
		node->color = ft_atoi_base(comma + 3, 16);
	}
	else
	{
		if (ft_safe_atoi(token, &value) == 0)
			return (0);
		node->z = value;
		node->color = 0xFFFFFF;
	}
	if (node->color == 0x000000)
		node->color = 0xFFFFFF;
	return (1);
}

void	ft_malloc_matrix(t_fdf *file_map)
{
	int	i;

	file_map->matrix = malloc(sizeof(t_node *) * file_map->height);
	if (!file_map->matrix)
		ft_free_exit(file_map, "Parsing error: malloc failed\n", 1, 1);
	i = 0;
	while (i < file_map->height)
	{
		file_map->matrix[i] = malloc(sizeof(t_node) * file_map->width);
		if (!file_map->matrix[i])
			ft_free_exit(file_map, "Parsing error: malloc failed\n", 1, 1);
		i++;
	}
}

/* Validates if an hexadecimal starts in 0x */
int	is_valid_hexa(const char *str)
{
	if (ft_strlen(str) < 3)
		return (0);
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (0);
	return (1);
}