/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:21 by slangero          #+#    #+#             */
/*   Updated: 2025/05/06 16:19:56 by slangero         ###   ########.fr       */
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
		return (1); // Out of bounds vertically
	}

	// We know y is valid, so map->map[y] and map->line_len[y] should be safe to access.
	// 2. Check horizontal bounds (x)
	if (x < 0 || x >= map->line_len[y])
	{
		return (1); // Out of bounds horizontally
	}

	// 3. Check if the character is a space
	if (map->map[y][x] == ' ')
	{
		return (1); // Neighbor is a space
	}

	// If none of the above, the neighbor is valid in terms of map closure rules
	return (0);
}

int validate_map_walls(t_map *map)
{
	int i; // Row index
	int j; // Column index
	int num_rows;
	char current_char;

	// Calculate the number of rows once
	num_rows = 0;
	if (map && map->map) // Basic null check
	{
		while (map->map[num_rows])
			num_rows++;
	}
	if (num_rows == 0)
		return (0); // Or handle as appropriate error

	i = 0;
	while (i < num_rows) // Iterate through rows
	{
		j = 0;
		while (j < map->line_len[i]) // Iterate through columns
		{
			current_char = map->map[i][j];
			// Check only floor ('0') and player ('N','S','E','W') tiles
			if (current_char == '0' || ft_strchr("NSEW", current_char))
			{
				// Check all 4 neighbors using the helper function
				// If ANY neighbor is invalid (returns 1), the map is not closed.
				if (is_invalid_neighbor(map, j + 1, i, num_rows) || // Check right
					is_invalid_neighbor(map, j - 1, i, num_rows) || // Check left
					is_invalid_neighbor(map, j, i + 1, num_rows) || // Check down
					is_invalid_neighbor(map, j, i - 1, num_rows))   // Check up
				{
					// Found an exposed '0' or Player character
					ft_putstr_fd("Error\nMap not surrounded by walls\n", 2);
					return (0); // Return error
				}
			}
			j++;
		}
		i++;
	}

	// If we looped through the whole map without finding exposed characters, it's closed.
	return (1); // Map is validly closed
}

int validate_map(t_map *map)
{
	if (!map || !map->map) // Add basic null checks
		return (0);
	if (!validate_player_position(map))
		return (0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}