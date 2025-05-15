/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:29:21 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 21:18:47 by agoldber         ###   ########.fr       */
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
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (p_err("No player position in map"), 0);
	if (player_count > 1)
		return (p_err("Multiple player positions in map"), 0);
	return (1);
}

int	neighbor(t_map *map, int x, int y, int num_rows)
{
	if (y < 0 || y >= num_rows)
		return (1);
	if (x < 0 || x >= map->line_len[y])
		return (1);
	if (map->map[y][x] == ' ')
		return (1);
	return (0);
}

int	validate_map_walls(t_map *m)
{
	int		i;
	int		j;
	int		r;
	char	current_char;

	r = 0;
	if (m && m->map)
		while (m->map[r])
			r++;
	if (r == 0)
		return (0);
	i = -1;
	while (++i < r)
	{
		j = -1;
		while (++j < m->line_len[i])
		{
			current_char = m->map[i][j];
			if (current_char == '0' || ft_strchr("NSEW", current_char))
				if (neighbor(m, j + 1, i, r) || neighbor(m, j - 1, i, r)
					|| neighbor(m, j, i + 1, r) || neighbor(m, j, i - 1, r))
					return (p_err("Map not surrounded by walls"), 0);
		}
	}
	return (1);
}

int	validate_map(t_map *map)
{
	if (!map || !map->map)
		return (0);
	if (!validate_player_position(map))
		return (0);
	if (!validate_map_walls(map))
		return (0);
	return (1);
}
