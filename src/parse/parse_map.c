/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/04/30 16:00:45 by slangero         ###   ########.fr       */
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
	size_t	len;

	printf("Reading file: %s\n", file_path);
	printf("Line count: %d\n", line_count);
	
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
		len = ft_strlen(line);
		// Remove newline character if present
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		
		printf("Read line %d: '%s'\n", i, line);
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static int	parse_rgb(char *str)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;
	int		i;
	int		color;

	// Debug output
	printf("Parsing RGB: '%s'\n", str);
	
	// Trim leading/trailing spaces
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
		
	// Manual parsing to handle potential issues
	if (sscanf(str, "%d,%d,%d", &r, &g, &b) == 3)
	{
		printf("Parsed using sscanf: %d,%d,%d\n", r, g, b);
		if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		{
			color = (r << 16) | (g << 8) | b;
			printf("Calculated color: %d\n", color);
			return (color);
		}
		else
		{
			printf("RGB values out of range (0-255)\n");
			return (0);
		}
	}
	
	// If sscanf fails, try the split method
	printf("Trying alternative parsing method\n");
	rgb_parts = ft_split(str, ',');
	if (!rgb_parts)
	{
		printf("Failed to split RGB string\n");
		return (0);
	}
	
	// Check if we have exactly 3 parts
	i = 0;
	while (rgb_parts[i])
	{
		printf("Part %d: '%s'\n", i, rgb_parts[i]);
		i++;
	}
	
	if (i != 3)
	{
		printf("RGB needs exactly 3 parts, found %d\n", i);
		free_array(rgb_parts);
		return (0);
	}
	
	// Convert to integers and validate range
	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	
	printf("RGB values: %d,%d,%d\n", r, g, b);
	
	free_array(rgb_parts);
	
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("RGB values out of range (0-255)\n");
		return (0);
	}
	
	color = (r << 16) | (g << 8) | b;
	printf("Calculated color: %d\n", color);
	return (color);
}

static int	parse_texture_paths(char **lines, t_map *map)
{
	int	i;
	int	count;
	char *trimmed;

	i = 0;
	count = 0;
	printf("Parsing texture paths and colors...\n");
	
	while (lines[i])
	{
		printf("Processing line: '%s'\n", lines[i]);
		
		if (ft_strncmp(lines[i], "NO ", 3) == 0 && !map->no_path)
		{
			trimmed = lines[i] + 3;
			while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
				trimmed++;
			map->no_path = ft_strdup(trimmed);
			printf("Found NO texture: %s\n", map->no_path);
			count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0 && !map->so_path)
		{
			trimmed = lines[i] + 3;
			while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
				trimmed++;
			map->so_path = ft_strdup(trimmed);
			printf("Found SO texture: %s\n", map->so_path);
			count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0 && !map->we_path)
		{
			trimmed = lines[i] + 3;
			while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
				trimmed++;
			map->we_path = ft_strdup(trimmed);
			printf("Found WE texture: %s\n", map->we_path);
			count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0 && !map->ea_path)
		{
			trimmed = lines[i] + 3;
			while (*trimmed && (*trimmed == ' ' || *trimmed == '\t'))
				trimmed++;
			map->ea_path = ft_strdup(trimmed);
			printf("Found EA texture: %s\n", map->ea_path);
			count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0 && map->floor_color == 0)
		{
			map->floor_color = parse_rgb(lines[i] + 2);
			if (map->floor_color != 0)
			{
				printf("Found floor color: %d\n", map->floor_color);
				count++;
			}
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0 && map->ceiling_color == 0)
		{
			map->ceiling_color = parse_rgb(lines[i] + 2);
			if (map->ceiling_color != 0)
			{
				printf("Found ceiling color: %d\n", map->ceiling_color);
				count++;
			}
		}
		i++;
	}
	printf("Found %d of 6 required elements\n", count);
	return (count == 6); // Make sure we have all 6 required elements
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
	map->line_len = malloc(sizeof(int) * map_lines);
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

	printf("\n--- STARTING MAP PARSING ---\n");
	
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

	printf("\n--- PARSING TEXTURES AND COLORS ---\n");
	if (!parse_texture_paths(lines, &map))
	{
		ft_putstr_fd("Error\nInvalid or missing texture/color information\n", 2);
		printf("Texture paths: NO=%s, SO=%s, WE=%s, EA=%s\n", 
			map.no_path ? map.no_path : "NULL", 
			map.so_path ? map.so_path : "NULL",
			map.we_path ? map.we_path : "NULL", 
			map.ea_path ? map.ea_path : "NULL");
		printf("Colors: Floor=%d, Ceiling=%d\n", map.floor_color, map.ceiling_color);
		free_array(lines);
		return (map);
	}

	printf("\n--- EXTRACTING MAP DATA ---\n");
	if (!extract_map_data(lines, &map))
	{
		ft_putstr_fd("Error\nInvalid map data\n", 2);
		free_array(lines);
		return (map);
	}

	printf("\n--- MAP PARSING COMPLETE ---\n");
	free_array(lines);
	return (map);
}


/*
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
		// Remove newline character if present
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

static int	parse_rgb(char *str)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb_parts = ft_split(str, ',');
	if (!rgb_parts)
		return (0);
	
	// Check if we have exactly 3 parts
	i = 0;
	while (rgb_parts[i])
		i++;
	if (i != 3)
	{
		free_array(rgb_parts);
		return (0);
	}
	
	// Convert to integers and validate range
	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	free_array(rgb_parts);
	
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
		
	return ((r << 16) | (g << 8) | b);
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
			map->floor_color = parse_rgb(lines[i] + 2);
			count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0 && map->ceiling_color == 0)
		{
			map->ceiling_color = parse_rgb(lines[i] + 2);
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
	map->line_len = malloc(sizeof(int) * map_lines);
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

*/