/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernafer <fernafer@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:24:00 by fernafer          #+#    #+#             */
/*   Updated: 2025/10/29 23:17:51 by fernafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}

static int	skip_space_sign(const char *str, int *sign)
{
	int		i;

	i = 0;
	*sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_safe_atoi(const char *nptr, int *out)
{
	int		i;
	int		sign;
	long	num;

	i = skip_space_sign(nptr, &sign);
	num = 0;
	if (!ft_isdigit(nptr[i]))
		return (0);
	while (ft_isdigit(nptr[i]))
	{
		num = num * 10 + (nptr[i] - '0');
		if (sign == 1 && num > 2147483647)
			return (0);
		if (sign == -1 && num < -2147483648)
			return (0);
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	*out = (int)(sign * num);
	return (1);
}
