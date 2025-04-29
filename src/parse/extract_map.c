/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:22 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 17:38:15 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && 
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && 
			line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	count_map_lines(t_parse_buffer *buffer, int start_idx)
{
	int	i;
	int	count;
	int	found_map;

	i = start_idx;
	count = 0;
	found_map = 0;
	while (i < buffer->line_count)
	{
		if (buffer->lines[i] && is_map_line(buffer->lines[i]))
		{
			count++;
			found_map = 1;
		}
		else if (found_map)
			break;
		i++;
	}
	return (count);
}

int	extract_map_data(t_parse_buffer *buffer, t_map *map)
{
	int	map_start;
	int	map_lines;
	int	i;
	int	j;

	map_start = find_map_start(buffer);
	if (map_start == -1)
		return (0);
	map_lines = count_map_lines(buffer, map_start);
	if (map_lines == 0)
		return (0);
	map->map = malloc(sizeof(char *) * (map_lines + 1));
	map->line_len = malloc(sizeof(int) * map_lines);
	if (!map->map || !map->line_len)
		return (0);
	i = 0;
	j = map_start;
	while (i < map_lines && j < buffer->line_count)
	{
		if (buffer->lines[j] && is_map_line(buffer->lines[j]))
		{
			map->map[i] = ft_strdup(buffer->lines[j]);
			if (!map->map[i])
				return (clean_map_data(map), 0);
			map->line_len[i] = ft_strlen(map->map[i]);
			i++;
		}
		j++;
	}
	map->map[i] = NULL;
	return (1);
}

void	clean_map_data(t_map *map)
{
	int	i;

	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	if (map->line_len)
	{
		free(map->line_len);
		map->line_len = NULL;
	}
}