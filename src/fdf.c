/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:31:30 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:03:43 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	error(int errno)
{
	if (errno == 0)
		ft_putendl_fd("Error: Invalid number of arguments", 2);
	else if (errno == 1)
		ft_putendl_fd("Error: Wrong file type", 2);
	else if (errno == 2)
		ft_putendl_fd("Error: Invalid map", 2);
	else if (errno == 3)
		ft_putendl_fd("Error: No permission to access file", 2);
	else if (errno == 5)
		ft_putendl_fd("Error: Failed to initialize connection to display", 2);
	else if (errno == 6)
		ft_putendl_fd("Error: Failed to create an image", 2);
	else if (errno == 7)
		ft_putendl_fd("Error: Failed to push image to window", 2);
}

static int	file_validator(char	*file)
{
	int		length;
	char	*filetype;

	filetype = ".fdf";
	length = ft_strlen(file);
	return (ft_strncmp(&file[length - 4], filetype, 4));
}

static void	initializer(t_map *map_specs)
{
	char		***temp;

	temp = NULL;
	map_specs->cols = 0;
	map_specs->rows = 0;
	map_specs->map = temp;
	map_specs->sq_size = 100;
	map_specs->img = 0;
	map_specs->scale = 1;
	map_specs->mlx = 0;
}

static int	controller(char *filename)
{
	int		fd;
	t_map	map_specs;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		error(3);
		return (ERROR);
	}
	initializer(&map_specs);
	if (map_reader(fd, &map_specs) > 0)
	{
		close(fd);
		if (run_mlx(&map_specs))
		{
			free_map(&map_specs);
			return (SUCCESS);
		}
		free_map(&map_specs);
		return (ERROR);
	}
	close(fd);
	error(2);
	return (ERROR);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (file_validator(argv[1]) == 0)
		{
			if (controller(argv[1]) > 0)
			{
				return (SUCCESS);
			}
			return (ERROR);
		}
		error(1);
		return (ERROR);
	}
	error(0);
	return (ERROR);
}
