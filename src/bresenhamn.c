/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenhamn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 07:12:47 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/11 07:21:20 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_coordintates_horiz(t_map *map_specs, t_coord *start, t_coord *horiz,
int offset)
{
	horiz->x = start->x + map_specs->sq_size * cos((M_PI / 180.0) * 30)
		* offset;
	horiz->y = start->y + map_specs->sq_size * sin((M_PI / 180.0) * 30)
		* offset;
}

void	set_coordinates_vert(t_map *map_specs, t_coord *start, t_coord *vert)
{
	vert->x = start->x - map_specs->sq_size * cos((M_PI / 180.0) * 30);
	vert->y = start->y + map_specs->sq_size * sin((M_PI / 180.0) * 30);
}

static t_bresenhamn	set_specs(t_bresenhamn *specs, t_coord *start, t_coord *end)
{
	specs->x_increment = -1;
	specs->y_increment = -1;
	if (start->x < end->x)
		specs->x_increment = 1;
	if (start->y < end->y)
		specs->y_increment = 1;
	specs->diff_x = abs(end->x - start->x);
	specs->diff_y = -abs(end->y - start->y);
	specs->error = specs->diff_x + specs->diff_y;
	return (*specs);
}

static int	update_coord(t_bresenhamn *specs, t_coord *start, t_coord *end)
{
	int	error_correction;

	error_correction = 2 * specs->error;
	if (error_correction >= specs->diff_y)
	{
		if (start->x == end->x)
			return (0);
		specs->error = specs->error + specs->diff_y;
		start->x = start->x + specs->x_increment;
	}
	if (error_correction <= specs->diff_x)
	{
		if (start->y == end->y)
			return (0);
		specs->error = specs->error + specs->diff_x;
		start->y = start->y + specs->y_increment;
	}
	return (1);
}

void	draw_line(mlx_image_t *img, t_coord *start, t_coord *end)
{
	t_bresenhamn	specs;

	specs = set_specs(&specs, start, end);
	while (1)
	{
		if (start->x >= WIDTH || start->y >= HEIGHT
			|| start->x < 0 || start->y < 0)
			break ;
		mlx_put_pixel(img, start->x, start->y, 0xFFFFFFFF);
		if (start->x == end->x && start->y == end->y)
			break ;
		if (update_coord(&specs, start, end) == 0)
			break ;
	}
}
