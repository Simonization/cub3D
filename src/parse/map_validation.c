/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:21 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:07 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_player_position(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (j < map->line_len[i])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		ft_putstr_fd("Error\nNo player position in map\n", 2);
		return (0);
	}
	if (player_count > 1)
	{
		ft_putstr_fd("Error\nMultiple player positions in map\n", 2);
		return (0);
	}
	return (1);
}

static int is_invalid_neighbor(t_map *map, int x, int y, int num_rows)
{
	if (y < 0 || y >= num_rows)
	{
		return (1);
	}
	if (x < 0 || x >= map->line_len[y])
	{
		return (1);
	}
	if (map->map[y][x] == ' ')
	{
		return (1);
	}
	return (0);
}

int validate_map_walls(t_map *map)
{
	int i;
	int j;
	int num_rows;
	char current_char;

	num_rows = 0;
	if (map && map->map)
		while (map->map[num_rows])
			num_rows++;
	if (num_rows == 0)
		return (0);
	i = 0;
	while (i < num_rows)
	{
		j = 0;
		while (j < map->line_len[i])
		{
			current_char = map->map[i][j];
			if (current_char == '0' || ft_strchr("NSEW", current_char))
			{
				if (is_invalid_neighbor(map, j + 1, i, num_rows) ||
					is_invalid_neighbor(map, j - 1, i, num_rows) ||
					is_invalid_neighbor(map, j, i + 1, num_rows) ||
					is_invalid_neighbor(map, j, i - 1, num_rows))
				{
					ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

int validate_map(t_map *map)
{
	if (!map || !map->map)
		return (0);
	if (!validate_player_position(map))
		return (0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}