/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/05/09 15:32:23 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (!line[i])
		return (0);
	if (line[i] != '0' && line[i] != '1'
		&& line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'E' && line[i] != 'W')
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1'
			&& line[i] != ' ' && line[i] != '\t'
			&& line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	count_map_lines(char **lines, int start_idx)
{
	int		i;
	int		count;
	int		found_map_content;
	char	*trimmed_line;

	i = start_idx;
	count = 0;
	found_map_content = 0;
	while (lines[i])
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n");
		if (!trimmed_line)
		{
			ft_putstr_fd("Error: Malloc failed in count_map_lines\n", 2);
			return (-1);
		}
		if (is_map_line(trimmed_line))
		{
			count++;
			found_map_content = 1;
		}
		else if (trimmed_line[0] == '\0' && found_map_content)
		{
			free(trimmed_line);
			break ;
		}
		else if (found_map_content)
		{
			free(trimmed_line);
			break ;
		}
		free(trimmed_line);
		i++;
	}
	return (count);
}

int	extract_map_data(char **lines, t_map *map, int map_content_start_index)
{
	int		map_actual_start_line_idx;
	char	*trimmed_line;
	int		is_map;
	int		map_lines_count;
	char	*current_line_trimmed;
	int		i;
	int		j;

	map_actual_start_line_idx = map_content_start_index;
	while (lines[map_actual_start_line_idx])
	{
		trimmed_line = ft_strtrim(lines[map_actual_start_line_idx], " \t\n");
		if (!trimmed_line)
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Malloc failed in extract_map_data\n", 2);
			return (0);
		}
		is_map = is_map_line(trimmed_line);
		free(trimmed_line);
		if (is_map)
			break ;
		map_actual_start_line_idx++;
	}
	if (!lines[map_actual_start_line_idx])
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("No map after texture/color definitions.\n", 2);
		return (0);
	}
	map_lines_count = count_map_lines(lines, map_actual_start_line_idx);
	if (map_lines_count <= 0)
	{
		ft_putstr_fd("Error\nNo valid map lines found.\n", 2);
		return (0);
	}
	map->map = malloc(sizeof(char *) * (map_lines_count + 1));
	map->line_len = ft_calloc(map_lines_count + 1, sizeof(int));
	if (!map->map || !map->line_len)
	{
		ft_putstr_fd("Error\nMalloc failed for map structure.\n", 2);
		free(map->map);
		free(map->line_len);
		map->map = NULL;
		map->line_len = NULL;
		return (0);
	}
	map->map_height = map_lines_count;
	map->map_width = 0;
	i = 0;
	j = map_actual_start_line_idx;
	while (i < map_lines_count && lines[j])
	{
		current_line_trimmed = ft_strtrim(lines[j], " \t\n");
		if (!current_line_trimmed)
		{
			free_array(map->map);
			free(map->line_len);
			map->map = NULL;
			map->line_len = NULL;
			return (0);
		}
		if (is_map_line(current_line_trimmed))
		{
			map->map[i] = ft_strdup(lines[j]);
			if (!map->map[i])
			{
				free_array(map->map);
				free(map->line_len);
				map->map = NULL;
				map->line_len = NULL;
				free(current_line_trimmed);
				return (0);
			}
			map->line_len[i] = ft_strlen(map->map[i]);
			if (map->line_len[i] > map->map_width)
				map->map_width = map->line_len[i];
			i++;
		}
		free(current_line_trimmed);
		j++;
		if (i == map_lines_count && lines[j]
			&& is_map_line(ft_strtrim(lines[j], " \t\n")))
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("Map disjointed or invalid empty lines in map.\n", 2);
			free_array(map->map);
			free(map->line_len);
			map->map = NULL;
			map->line_len = NULL;
			return (0);
		}
	}
	map->map[i] = NULL;
	if (i != map_lines_count)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Mismatch: counted map VS extracted lines.\n", 2);
		free_array(map->map);
		free(map->line_len);
		map->map = NULL;
		map->line_len = NULL;
		return (0);
	}
	return (1);
}
