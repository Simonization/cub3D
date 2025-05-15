/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 21:03:41 by agoldber         ###   ########.fr       */
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
	int		count;
	int		found_map_content;
	char	*trimmed_line;

	count = 0;
	found_map_content = 0;
	while (lines[start_idx])
	{
		trimmed_line = ft_strtrim(lines[start_idx], " \t\n");
		if (!trimmed_line)
			return (p_err("Memory allocation failed"), -1);
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
		free(trimmed_line);
		start_idx++;
	}
	return (count);
}

void	check(char **lines, int map_content_start_index, t_map *map)
{
	int	i;
	int	j;

	i = map_content_start_index;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] != 'N' && lines[i][j] != 'S'
				&& lines[i][j] != 'E' && lines[i][j] != 'W'
				&& lines[i][j] != '0' && lines[i][j] != '1'
				&& lines[i][j] != ' ')
			{
				free_array(lines);
				ft_exit(1, "Error\nInvalid character in map area\n", map);
			}
			j++;
		}
		i++;
	}
}

int	get_start_index(char **lines, int *start)
{
	char	*trimmed_line;
	int		is_map;

	while (lines[*start])
	{
		trimmed_line = ft_strtrim(lines[*start], " \t\n");
		if (!trimmed_line)
			return (p_err("Memory allocation failed"), 0);
		is_map = is_map_line(trimmed_line);
		free(trimmed_line);
		if (is_map)
			break ;
		(*start)++;
	}
	if (!lines[*start])
		return (p_err("No map after texture/color definitions."), 0);
	return (1);
}

int	fill_map(t_map *map, int j, int map_lines_count, char **lines)
{
	char	*trim;
	int		i;

	i = 0;
	while (i < map_lines_count && lines[j])
	{
		trim = ft_strtrim(lines[j], " \t\n");
		if (!trim)
			return (p_err("Memory allocation failed"), 0);
		if (is_map_line(trim))
		{
			map->map[i] = ft_strdup(lines[j]);
			if (!map->map[i])
				return (free(trim), p_err("Memory allocation failed"), 0);
			i++;
		}
		free(trim);
		j++;
		if (i == map_lines_count && lines[j]
			&& is_map_line(ft_strtrim(lines[j], " \t\n")))
			return (p_err("Map disjointed or invalid empty lines in map."), 0);
	}
	if (i != map_lines_count)
		return (p_err("Mismatch: counted map VS extracted lines."), 0);
	return (1);
}

int	extract_map_data(char **lines, t_map *map, int map_content_start_index)
{
	int		map_lines_count;
	int		i;

	check(lines, map_content_start_index, map);
	if (!get_start_index(lines, &map_content_start_index))
		return (0);
	map_lines_count = count_map_lines(lines, map_content_start_index);
	if (map_lines_count <= 0)
		return (0);
	map->map = ft_calloc(sizeof(char *), (map_lines_count + 1));
	// map->line_len = ft_calloc(map_lines_count + 1, sizeof(int));
	map->line_len = NULL;
	if (!map->map || !map->line_len)
		return (p_err("Memory allocation failed"), 0);
	if (!fill_map(map, map_content_start_index, map_lines_count, lines))
		return (0);
	i = -1;
	while (map->map[++i])
		map->line_len[i] = ft_strlen(map->map[i]);
	return (1);
}
