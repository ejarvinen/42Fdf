/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:08:29 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:09:10 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_fdf_strlen(char *str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len] != ',' && str[len] != '\0')
			len++;
	}
	return (len);
}

static int	validate_point(char *point)
{
	int	len;
	int	index;
	int	error;

	if (!point)
		return (ERROR);
	index = 0;
	error = 0;
	len = ft_fdf_strlen(point);
	while (index < len)
	{
		if (ft_isdigit(point[index]) == 0)
		{
			if ((point[index] != '-' && index == 0) && (point[index] != '+'
					&& index == 0) && !(point[index] == '\n'
					&& index != len - 1))
				error++;
		}
		index++;
	}
	if (len == index - error)
		return (SUCCESS);
	return (ERROR);
}

static int	ft_fdf_atoi(const char *str)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = nbr * 10;
		nbr = nbr + (*str - 48);
		str++;
		if (nbr < 0 && sign < 0)
			return (0);
		if (nbr < 0 && sign > 0)
			return (-1);
	}
	if (*str == '\0' || *str == ',' || *str == '\n')
		return ((int)nbr * sign);
	return (0);
}

static int	check_for_overflow(char *array)
{
	if ((array[0] == '-' && ft_fdf_atoi(array) >= 0) || (array[0] != '-'
			&& ft_fdf_atoi(array) < 0) || ft_atoi(array) != ft_fdf_atoi(array))
		return (ERROR);
	return (SUCCESS);
}

int	verify_line(char *row)
{
	char	**line;
	int		index;

	line = ft_split(row, ' ');
	if (line)
	{
		index = 0;
		while (line[index])
		{
			if (line[index][0] == '\n' && line[index + 1] == NULL)
				break ;
			if (validate_point(line[index]) < 0
				|| check_for_overflow(line[index]) < 0)
			{
				free_line(line);
				return (ERROR);
			}
			index++;
		}
		free_line(line);
		return (index);
	}
	return (ERROR);
}
