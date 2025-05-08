/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/05/07 19:31:00 by slangero         ###   ########.fr       */
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

static int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	count_map_lines(char **lines, int start_idx)
{
	int	i;
	int	count;
	int	found_map;

	i = start_idx;
	count = 0;
	found_map = 0;
	while (lines[i])
	{
		if (is_map_line(lines[i]))
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

int	extract_map_data(char **lines, t_map *map)
{
	int	map_start;
	int	map_lines;
	int	i;
	int	j;

	map_start = find_map_start(lines);
	if (map_start == -1)
		return (0);
		
	map_lines = count_map_lines(lines, map_start);
	if (map_lines == 0)
		return (0);
		
	map->map = malloc(sizeof(char *) * (map_lines + 1));
	map->line_len = ft_calloc(map_lines + 1, sizeof(int));
	if (!map->map || !map->line_len)
		return (0);
		
	i = 0;
	j = map_start;
	while (i < map_lines && lines[j])
	{
		if (is_map_line(lines[j]))
		{
			map->map[i] = ft_strdup(lines[j]);
			if (!map->map[i])
				return (0);
			map->line_len[i] = ft_strlen(map->map[i]);
			i++;
		}
		j++;
	}
	map->map[i] = NULL;
	return (1);
}