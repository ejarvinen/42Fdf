/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 07:09:19 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/13 13:54:22 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	*set_background_color(mlx_image_t *img)
{
	int	rows;
	int	cols;

	cols = 0;
	while (cols < HEIGHT)
	{
		rows = 0;
		while (rows < WIDTH)
		{
			mlx_put_pixel(img, rows, cols, 0x000000FF);
			rows++;
		}
		cols++;
	}
	return (img);
}

static void	draw_map(t_map *map_specs)
{
	t_coord		end;
	t_coord		start;

	map_specs->img = mlx_new_image(map_specs->mlx, WIDTH, HEIGHT);
	if (!map_specs->img)
		error(6);
	else
	{
		set_background_color(map_specs->img);
		set_start_coordinates(&start, map_specs);
		iterate_map(map_specs, &start, &end);
		if (mlx_image_to_window(map_specs->mlx, map_specs->img, 0, 0) < 0)
		{
			error(7);
			mlx_delete_image(map_specs->mlx, map_specs->img);
		}
	}
}

static void	close_window(void *param)
{
	t_map	*map_specs;

	map_specs = param;
	if (mlx_is_key_down(map_specs->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(map_specs->mlx);
		mlx_delete_image(map_specs->mlx, map_specs->img);
	}
}

int	run_mlx(t_map *map_specs)
{
	map_specs->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!map_specs->mlx)
	{
		error(5);
		return (ERROR);
	}
	draw_map(map_specs);
	if (map_specs->img)
	{
		mlx_loop_hook(map_specs->mlx, &close_window, map_specs);
		mlx_loop(map_specs->mlx);
		mlx_terminate(map_specs->mlx);
		return (SUCCESS);
	}
	mlx_terminate(map_specs->mlx);
	return (ERROR);
}
