/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_map_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 06:24:24 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:06:37 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_line(char **str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	while (len >= 0)
	{
		free(str[len]);
		len--;
	}
	free(str);
}

void	free_map(t_map *map_specs)
{
	int	index;
	int	sub_strs;

	sub_strs = map_specs->rows - 1;
	while (sub_strs >= 0)
	{
		index = map_specs->cols;
		while (index >= 0)
		{
			free(map_specs->map[sub_strs][index]);
			index--;
		}
		free(map_specs->map[sub_strs]);
		sub_strs--;
	}
	free(map_specs->map);
}

static int	populate_map(t_list *head, t_map *map_specs, int index)
{
	void	*contents;

	contents = head->content;
	map_specs->map[index] = ft_split((const char *)contents, ' ');
	if (!map_specs->map[index])
	{
		free_map(map_specs);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	setup_map(t_list *head, t_map *map_specs)
{
	int	index;

	map_specs->map = (char ***)malloc(sizeof(char **) * (map_specs->rows + 1));
	if (!map_specs->map)
		return (ERROR);
	index = 0;
	while (head->next)
	{
		if (populate_map(head, map_specs, index) > 0)
		{
			head = head->next;
			index++;
		}
		else
			return (ERROR);
	}
	if (populate_map(head, map_specs, index) > 0)
	{
		index++;
		map_specs->map[index] = NULL;
		return (SUCCESS);
	}
	return (ERROR);
}

int	map_reader(int fd, t_map *map_specs)
{
	t_list	*lines;

	lines = create_list(fd, map_specs);
	if (!lines || map_specs->rows < 2)
	{
		ft_lstclear(&lines, free);
		return (ERROR);
	}
	if (setup_map(lines, map_specs) > 0)
	{
		ft_lstclear(&lines, free);
		return (SUCCESS);
	}
	ft_lstclear(&lines, free);
	return (ERROR);
}
