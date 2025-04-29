/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:15:27 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 18:19:17 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int validate_characters_and_player(t_map *map)
{
	int	player_count = 0;
	int	i = 0;
	
	while (map->map[i])
	{
		int j = 0;
		while (j < map->line_len[i])
		{
			char c = map->map[i][j];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && 
				c != 'E' && c != 'W' && c != ' ')
				return (ft_putstr_fd("Error\nInvalid character in map\n", 2), 0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
				
			j++;
		}
		i++;
	if (player_count == 0)
		return (ft_putstr_fd("Error\nNo player position found in map\n", 2), 0);
	else if (player_count > 1)
		return (ft_putstr_fd("Error\nMultiple player positions found in map\n", 2), 0);
	return (1);
}

static int check_map_borders(t_map *map)
{
	int	height = 0;
	
	while (map->map[height])
		height++;
		
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < map->line_len[i]; j++)
		{
			char c = map->map[i][j];
			if (c == ' ')
				continue;
			if ((i == 0 || i == height - 1 || j == 0 || j == map->line_len[i] - 1) && c != '1')
				return (ft_putstr_fd("Error\nMap not surrounded by walls\n", 2), 0);
			if (c != '1' && c != ' ')
			{
				int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
				for (int d = 0; d < 4; d++)
				{
					int ni = i + directions[d][0];
					int nj = j + directions[d][1];
					if (ni < 0 || ni >= height || nj < 0 || nj >= map->line_len[ni])
						return (ft_putstr_fd("Error\nMap not surrounded by walls\n", 2), 0);
					if (map->map[ni][nj] == ' ')
						return (ft_putstr_fd("Error\nMap has invalid layout\n", 2), 0);
				}
			}
		}
	}
	
	return (1);
}

static void flood_fill(char **map, int i, int j, int height, int *line_len, int *is_valid)
{
	if (i < 0 || i >= height || j < 0 || j >= line_len[i] || 
		map[i][j] == '1' || map[i][j] == 'V' || map[i][j] == ' ')
		return;
	map[i][j] = 'V';
	if (i == 0 || i == height - 1 || j == 0 || j == line_len[i] - 1)
	{
		*is_valid = 0;
		return;
	}

	flood_fill(map, i-1, j, height, line_len, is_valid);
	flood_fill(map, i+1, j, height, line_len, is_valid);
	flood_fill(map, i, j-1, height, line_len, is_valid);
	flood_fill(map, i, j+1, height, line_len, is_valid);
}

static int verify_map_integrity(t_map *map)
{
	int	height = 0;

	while (map->map[height])
		height++;
	int player_i = -1, player_j = -1;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < map->line_len[i]; j++)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player_i = i;
				player_j = j;
				break;
			}
		}
		if (player_i != -1)
			break;
	}
	char **map_copy = malloc(sizeof(char*) * (height + 1));
	if (!map_copy)
		return (ft_putstr_fd("Error\nMemory allocation failed\n", 2), 0);
	for (int i = 0; i < height; i++)
	{
		map_copy[i] = ft_strdup(map->map[i]);
		if (!map_copy[i])
		{
			for (int j = 0; j < i; j++)
				free(map_copy[j]);
			free(map_copy);
			return (ft_putstr_fd("Error\nMemory allocation failed\n", 2), 0);
		}
	}
	map_copy[height] = NULL;
	int is_valid = 1;
	flood_fill(map_copy, player_i, player_j, height, map->line_len, &is_valid);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < map->line_len[i]; j++)
		{
			if ((map_copy[i][j] == '0' || map_copy[i][j] == 'N' || map_copy[i][j] == 'S' ||
				 map_copy[i][j] == 'E' || map_copy[i][j] == 'W') && map_copy[i][j] != 'V')
			{
				is_valid = 0;
				break;
			}
		}
	}
	for (int i = 0; i < height; i++)
		free(map_copy[i]);
	free(map_copy);
	if (!is_valid)
		return (ft_putstr_fd("Error\nMap not properly enclosed by walls\n", 2), 0);
	return (1);
}

int validate_map(t_map *map)
{
	if (!validate_characters_and_player(map))
		return (0);
		
	if (!check_map_borders(map))
		return (0);
		
	if (!verify_map_integrity(map))
		return (0);
		
	return (1);
}