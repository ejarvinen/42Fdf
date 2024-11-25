/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:23:08 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:03:09 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	find_max(t_map *map_specs)
{
	int	rows;
	int	cols;
	int	max;

	rows = 0;
	max = 0;
	while (rows < map_specs->rows)
	{
		cols = 0;
		while (cols < map_specs->cols)
		{
			if (ft_atoi(map_specs->map[rows][cols]) > max)
				max = ft_atoi(map_specs->map[rows][cols]);
			cols++;
		}
		rows++;
	}
	return (max);
}

static int	find_min(t_map *map_specs)
{
	int	rows;
	int	cols;
	int	min;

	rows = 0;
	min = 0;
	while (rows < map_specs->rows)
	{
		cols = 0;
		while (cols < map_specs->cols)
		{
			if (ft_atoi(map_specs->map[rows][cols]) < min)
				min = ft_atoi(map_specs->map[rows][cols]);
			cols++;
		}
		rows++;
	}
	return (min);
}

static void	scale_determinator(t_map *map_specs, int max, int min)
{
	int	scale;

	if (max > abs(min))
		scale = max;
	else
		scale = abs(min);
	if (scale > 100)
		map_specs->scale = 0.05;
	else if (scale > 50)
		map_specs->scale = 0.08;
	else if (scale > 25)
		map_specs->scale = 0.25;
	else if (scale > 10)
		map_specs->scale = 0.5;
}

static void	set_center(t_coord *center, t_map *map_specs)
{
	if (map_specs->cols > map_specs->rows)
		center->x = map_specs->cols * map_specs->sq_size
			* sin((M_PI / 180.0) * 60);
	else
		center->x = -1 * map_specs->rows * map_specs->sq_size
			* sin((M_PI / 180.0) * 60);
	center->y = map_specs->cols * map_specs->sq_size * cos((M_PI / 180.0) * 60);
}

void	set_start_coordinates(t_coord *start, t_map *map_specs)
{
	int		max_depth;
	int		min_depth;
	t_coord	center;

	max_depth = find_max(map_specs);
	min_depth = find_min(map_specs);
	scale_determinator(map_specs, max_depth, min_depth);
	if (map_specs->cols > 199 || map_specs->rows > 199)
		map_specs->sq_size = 3;
	else if (map_specs->cols > 99 || map_specs->rows > 99)
		map_specs->sq_size = 5;
	else if (map_specs->cols > 49 || map_specs->rows > 49)
		map_specs->sq_size = 10;
	else if (map_specs->cols > 29 || map_specs->rows > 29)
		map_specs->sq_size = 15;
	else if (map_specs->cols > 14 || map_specs->rows > 14)
		map_specs->sq_size = 25;
	else if (map_specs->cols > 4 || map_specs->rows > 4)
		map_specs->sq_size = 35;
	set_center(&center, map_specs);
	if (abs(map_specs->cols - map_specs->rows) > 5)
		start->x = WIDTH / 2 - center.x / 2;
	else
		start->x = WIDTH / 2;
	start->y = HEIGHT / 2 - center.y;
}
