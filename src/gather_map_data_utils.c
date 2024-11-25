/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_map_data_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:11:44 by emansoor          #+#    #+#             */
/*   Updated: 2024/03/16 11:07:31 by emansoor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*initialize_list(int fd, t_map *map_specs)
{
	t_list	*head;
	char	*line;

	line = get_next_line(fd);
	if (line)
	{
		map_specs->cols = verify_line(line);
		if (map_specs->cols > 0)
		{
			head = ft_lstnew(line);
			if (!head || line[0] == '\n')
			{
				ft_lstclear(&head, free);
				return (NULL);
			}
			return (head);
		}
		free(line);
	}
	return (NULL);
}

static t_list	*build_list(int fd, t_list *head, t_map *map_specs)
{
	t_list	*new_line;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (verify_line(line) != map_specs->cols)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		new_line = ft_lstnew(line);
		if (!new_line)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new_line);
		line = get_next_line(fd);
	}
	return (head);
}

t_list	*create_list(int fd, t_map *map_specs)
{
	t_list	*head;

	head = initialize_list(fd, map_specs);
	if (!head)
		return (NULL);
	head = build_list(fd, head, map_specs);
	if (!head)
		return (NULL);
	map_specs->rows = ft_lstsize(head);
	return (head);
}
