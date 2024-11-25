/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:19:00 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:05:54 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1400
# define HEIGHT 1000

# define ERROR -1
# define SUCCESS 1

# define _USE_MATH_DEFINES

typedef struct s_map
{
	int			cols;
	int			rows;
	int			sq_size;
	float		scale;
	char		***map;
	mlx_image_t	*img;
	mlx_t		*mlx;
}			t_map;

typedef struct s_coord
{
	int		x;
	int		y;
}			t_coord;

typedef struct s_bresenhamn
{
	int	x_increment;
	int	y_increment;
	int	diff_x;
	int	diff_y;
	int	error;
}			t_bresenhamn;

int		main(int argc, char **argv);
int		map_reader(int fd, t_map *map_specs);
void	free_map(t_map *map_specs);
t_list	*create_list(int fd, t_map *map_specs);
int		verify_line(char *row);
void	free_line(char **str);
void	set_start_coordinates(t_coord *start, t_map *map_specs);
int		run_mlx(t_map *map_specs);
void	iterate_map(t_map *map_specs, t_coord *start, t_coord *horizontal);
void	draw_line(mlx_image_t *img, t_coord *start, t_coord *end);
void	set_coordinates_vert(t_map *map_specs, t_coord *start, t_coord *vert);
void	set_coordintates_horiz(t_map *map_specs, t_coord *start,
			t_coord *horiz, int offset);
void	error(int errno);

#endif