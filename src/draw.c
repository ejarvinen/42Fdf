/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:06:17 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:02:13 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	update_rowstart(t_map *map_specs, t_coord *start)
{
	start->x = start->x - map_specs->sq_size * cos((M_PI / 180.0) * 30);
	start->y = start->y + map_specs->sq_size * sin((M_PI / 180.0) * 30);
}

static void	draw_horizontal(t_map *map_specs, t_coord *start,
t_coord *horizontal, t_coord *map)
{
	t_coord	temp;
	int		z;
	int		z_next;

	set_coordintates_horiz(map_specs, start, &temp, map->x);
	set_coordintates_horiz(map_specs, start, horizontal, map->x + 1);
	z = ft_atoi(map_specs->map[map->y][map->x]);
	if (z != 0)
		temp.y = temp.y - z * map_specs->sq_size * map_specs->scale;
	z_next = ft_atoi(map_specs->map[map->y][map->x + 1]);
	if (z_next != 0)
		horizontal->y = horizontal->y - z_next * map_specs->sq_size
			* map_specs->scale;
	draw_line(map_specs->img, &temp, horizontal);
}

static void	draw_vertical(t_map *map_specs, t_coord *start, t_coord *map)
{
	t_coord	temp;
	t_coord	vertical;
	int		z;
	int		z_next;

	set_coordintates_horiz(map_specs, start, &temp, map->x);
	set_coordinates_vert(map_specs, &temp, &vertical);
	z = ft_atoi(map_specs->map[map->y][map->x]);
	if (z != 0)
		temp.y = temp.y - z * map_specs->sq_size * map_specs->scale;
	z_next = ft_atoi(map_specs->map[map->y + 1][map->x]);
	if (z_next != 0)
		vertical.y = vertical.y - z_next * map_specs->sq_size
			* map_specs->scale;
	draw_line(map_specs->img, &temp, &vertical);
}

void	iterate_map(t_map *map_specs, t_coord *start, t_coord *horizontal)
{
	t_coord	map_coord;

	map_coord.y = 0;
	while (map_coord.y < map_specs->rows)
	{
		map_coord.x = 0;
		while (map_coord.x < map_specs->cols)
		{
			if (map_coord.y == map_specs->rows - 1
				&& map_coord.x != map_specs->cols - 1)
				draw_horizontal(map_specs, start, horizontal, &map_coord);
			else if (map_coord.x == map_specs->cols - 1
				&& map_coord.y != map_specs->rows - 1)
				draw_vertical(map_specs, start, &map_coord);
			else if (map_coord.x < map_specs->cols - 1
				&& map_coord.y != map_specs->rows - 1)
			{
				draw_vertical(map_specs, start, &map_coord);
				draw_horizontal(map_specs, start, horizontal, &map_coord);
			}
			map_coord.x++;
		}
		update_rowstart(map_specs, start);
		map_coord.y++;
	}
}
