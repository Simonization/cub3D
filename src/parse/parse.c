/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:30:41 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 19:00:56 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_parse_buffer
{
	char **lines;
	int line_count;
} t_parse_buffer;

static t_parse_buffer read_file_to_buffer(char *filename)
{
	t_parse_buffer buffer;
	int fd;
	char *line;
	int i;
	int count;
	
	ft_bzero(&buffer, sizeof(t_parse_buffer));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (buffer);
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	buffer.lines = malloc(sizeof(char *) * (count + 1));
	buffer.line_count = count;
	if (!buffer.lines)
		return (buffer);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(buffer.lines);
		buffer.lines = NULL;
		return (buffer);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < count)
		buffer.lines[i++] = line;
	buffer.lines[i] = NULL;
	close(fd);
	
	return (buffer);
}

static int parse_identifiers(t_parse_buffer *buffer, t_map *map)
{
	int i;
	
	i = 0;
	while (buffer->lines[i])
	{
		if (ft_strncmp(buffer->lines[i], "NO ", 3) == 0)
			map->no_path = ft_strdup(buffer->lines[i] + 3);
		else if (ft_strncmp(buffer->lines[i], "SO ", 3) == 0)
			map->so_path = ft_strdup(buffer->lines[i] + 3);
		else if (ft_strncmp(buffer->lines[i], "WE ", 3) == 0)
			map->we_path = ft_strdup(buffer->lines[i] + 3);
		else if (ft_strncmp(buffer->lines[i], "EA ", 3) == 0)
			map->ea_path = ft_strdup(buffer->lines[i] + 3);
		else if (ft_strncmp(buffer->lines[i], "F ", 2) == 0)
			map->floor_color = parse_color(buffer->lines[i] + 2);
		else if (ft_strncmp(buffer->lines[i], "C ", 2) == 0)
			map->ceiling_color = parse_color(buffer->lines[i] + 2);
		i++;
	}
	return (1);
}

static int find_map_start(t_parse_buffer *buffer)
{
	int i;
	
	i = 0;
	while (buffer->lines[i])
	{
		if (buffer->lines[i][0] == '1' || buffer->lines[i][0] == '0')
			return (i);
		i++;
	}
	return (-1);
}

static int process_map_data(t_parse_buffer *buffer, t_map *map, int map_start)
{
	int map_lines;
	int i;
	
	map_lines = buffer->line_count - map_start;
	map->map = malloc(sizeof(char *) * (map_lines + 1));
	map->line_len = malloc(sizeof(int) * map_lines);
	if (!map->map || !map->line_len)
		return (0);
	
	i = 0;
	while (buffer->lines[map_start + i])
	{
		map->map[i] = ft_strdup(buffer->lines[map_start + i]);
		map->line_len[i] = ft_strlen(map->map[i]);
		i++;
	}
	map->map[i] = NULL;
	return (1);
}


int parse_map(char *file_path, t_map *final_map)
{
    t_parse_buffer buffer;
    t_map temp_map;
    
    // Initialize temporary map structure
    ft_bzero(&temp_map, sizeof(t_map));
    
    // Read file into buffer
    buffer = read_file_to_buffer(file_path);
    if (!buffer.lines)
        return (0);
    
    // Parse metadata (textures, colors)
    if (!parse_metadata(&buffer, &temp_map))
        return (cleanup_buffer(&buffer), clean_map_data(&temp_map), 0);
    
    // Extract and validate map
    if (!extract_map_data(&buffer, &temp_map) || !validate_map(&temp_map))
        return (cleanup_buffer(&buffer), clean_map_data(&temp_map), 0);
    
    // Populate final map structure
    if (!populate_map_structure(&buffer, &temp_map, final_map))
        return (cleanup_buffer(&buffer), clean_map_data(&temp_map), 0);
    
    // Clean up temporary resources
    cleanup_buffer(&buffer);
    clean_map_data(&temp_map);
    
    return (1);
}

/*
t_map parse_map(char *filename)
{
	t_map map;
	t_parse_buffer buffer;
	int map_start;
	
	ft_bzero(&map, sizeof(t_map));
	buffer = read_file_to_buffer(filename);
	if (!buffer.lines)
		return (map);
	
	parse_identifiers(&buffer, &map);
	
	map_start = find_map_start(&buffer);
	if (map_start == -1 || !process_map_data(&buffer, &map, map_start))
		clean_map(&map);
	cleanup_buffer(&buffer);
	
	return (map);
}
	*/