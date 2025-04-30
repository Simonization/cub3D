/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:21 by slangero          #+#    #+#             */
/*   Updated: 2025/04/30 14:29:49 by slangero         ###   ########.fr       */
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

static int	is_wall_or_outside(t_map *map, int x, int y)
{
	if (y < 0 || !map->map[y] || x < 0 || 
		x >= map->line_len[y] || map->map[y][x] == ' ')
		return (1);
	return (map->map[y][x] == '1');
}

int	validate_map_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (j < map->line_len[i])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != ' ')
			{
				if (!is_wall_or_outside(map, j + 1, i) || 
					!is_wall_or_outside(map, j - 1, i) ||
					!is_wall_or_outside(map, j, i + 1) ||
					!is_wall_or_outside(map, j, i - 1))
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

int	validate_map(t_map *map)
{
	if (!validate_player_position(map))
		return (0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}