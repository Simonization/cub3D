/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/05/07 13:14:07 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
}

static char	**read_file_to_array(char *file_path, int line_count)
{
	int		fd;
	int		i;
	char	*line;
	char	**lines;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < line_count)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int is_valid_rgb_component(char *component)
{
	int i;
	int value;

	if (!component || component[0] == '\0')
		return (-1);

	i = 0;
	while (component[i])
	{
		if (!ft_isdigit(component[i]))
			return (-1);
		i++;
	}
	value = ft_atoi(component);
	if (value < 0 || value > 255)
		return (-1);

	return (value);
}

static int parse_and_validate_rgb(char *rgb_string)
{
	char    **parts;
	char    *trimmed_parts[3];
	int     rgb[3];
	int     i;
	int     final_color;

	if (!rgb_string) return (-1);

	parts = ft_split(rgb_string, ',');
	if (!parts) return (-1);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_array(parts);
		return (-1);
	}
	final_color = -1;
	for (i = 0; i < 3; i++)
	{
		trimmed_parts[i] = ft_strtrim(parts[i], " \t\n");
		if (!trimmed_parts[i]) {
			 int k = 0;
			 while(k < i) free(trimmed_parts[k++]);
			 free_array(parts);
			 return -1;
		}
		rgb[i] = is_valid_rgb_component(trimmed_parts[i]);
		free(trimmed_parts[i]);

		if (rgb[i] == -1)
		{
			free_array(parts);
			return (-1);
		}
	}
	final_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_array(parts);
	return (final_color);
}

static int	parse_texture_paths(char **lines, t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0 && !map->no_path)
		{
			map->no_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0 && !map->so_path)
		{
			map->so_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0 && !map->we_path)
		{
			map->we_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0 && !map->ea_path)
		{
			map->ea_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0 && map->floor_color == 0)
		{
			char *value_str = lines[i] + 1;
			while (*value_str && ft_isspace(value_str)) value_str++;
			map->floor_color = parse_and_validate_rgb(value_str);
			if (map->floor_color == -1)
			{
				ft_putstr_fd("Error\nInvalid floor color format or value\n", 2);
				free_array(lines);
				exit(1);
			}
			count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0 && map->ceiling_color == 0)
		{
			char *value_str = lines[i] + 1;
			while (*value_str && ft_isspace(value_str)) value_str++;
			map->ceiling_color = parse_and_validate_rgb(value_str);
			if (map->ceiling_color == -1)
			{
				ft_putstr_fd("Error\nInvalid ceiling color format or value\n", 2);
				free_array(lines);
				exit(1);
			}
			count++;
		}
		i++;
	}
	return (count == 6);
}

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

static int	extract_map_data(char **lines, t_map *map)
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

t_map	parse_map(char *file_path)
{
	t_map	map;
	char	**lines;
	int		line_count;

	ft_bzero(&map, sizeof(t_map));
	line_count = count_lines(file_path);
	if (line_count <= 0)
	{
		ft_putstr_fd("Error\nFailed to read file or empty file\n", 2);
		return (map);
	}
	lines = read_file_to_array(file_path, line_count);
	if (!lines)
	{
		ft_putstr_fd("Error\nFailed to read file\n", 2);
		return (map);
	}

	if (!parse_texture_paths(lines, &map))
	{
		ft_putstr_fd("Error\nInvalid or missing texture/color information\n", 2);
		free_array(lines);
		return (map);
	}

	if (!extract_map_data(lines, &map))
	{
		ft_putstr_fd("Error\nInvalid map data\n", 2);
		free_array(lines);
		return (map);
	}

	free_array(lines);
	return (map);
}
