/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:18:33 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 18:15:55 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_texture_file(char *path)
{
    int     fd;
    char    buffer[10];
    ssize_t bytes_read;
    int     path_len;
    
    path_len = ft_strlen(path);
    if (path_len < 5 || ft_strncmp(path + path_len - 4, ".xpm", 4) != 0)
        return (0);
    fd = open(path, O_RDONLY);
    if (fd == -1)
        return (0);
    bytes_read = read(fd, buffer, 9);
    close(fd);
    if (bytes_read < 9 || ft_strncmp(buffer, "/* XPM */", 9) != 0)
        return (0);
    return (1);
}

static int parse_rgb_value(char *str, int *r, int *g, int *b)
{
	char **rgb_parts;
	int   values[3];
	int   i;
	
	rgb_parts = ft_split(str, ',');
	if (!rgb_parts)
		return (0);
	i = 0;
	while (rgb_parts[i])
		i++;
	if (i != 3)
	{
		free_array(rgb_parts);
		return (0);
	}
	i = 0;
	while (i < 3)
	{
		if (!ft_isnum(rgb_parts[i]))
		{
			free_array(rgb_parts);
			return (0);
		}
		values[i] = ft_atoi(rgb_parts[i]);
		if (values[i] < 0 || values[i] > 255)
		{
			free_array(rgb_parts);
			return (0);
		}
		i++;
	}
	*r = values[0];
	*g = values[1];
	*b = values[2];
	free_array(rgb_parts);
	return (1);
}

static int parse_color(char *color_str, int *color_value)
{
	int r;
	int g;
	int b;
	
	if (!parse_rgb_value(color_str, &r, &g, &b))
		return (0);      
	*color_value = (r << 16) | (g << 8) | b;
	return (1);
}

static int handle_texture(char *line, char **texture_path)
{
	char *trimmed;
	
	if (*texture_path)
		return (0);
	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (0);
		
	*texture_path = ft_strdup(trimmed);
	free(trimmed);
	
	if (!*texture_path || !check_texture_file(*texture_path))
		return (0);
		
	return (1);
}

static int handle_color(char *line, int *color_value)
{
	char *trimmed;
	int  result;
	
	if (*color_value != 0)
		return (0);
	trimmed = ft_strtrim(line, " \t");
	if (!trimmed)
		return (0);
	result = parse_color(trimmed, color_value);
	free(trimmed);
	return (result);
}

static int is_map_line(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
		
	if (*line == '0' || *line == '1' || *line == ' ')
		return (1);
		
	return (0);
}

int parse_metadata(t_parse_buffer *buffer, t_map *map)
{
	int  i;
	char *line;
	
	i = 0;
	while (i < buffer->line_count)
	{
		line = buffer->lines[i];
		if (!line || !*line)
		{
			i++;
			continue;
		}
		if (is_map_line(line))
			break;
			
		if (ft_strncmp(line, "NO ", 3) == 0)
		{
			if (!handle_texture(line + 3, &map->no_path))
				return (0);
		}
		else if (ft_strncmp(line, "SO ", 3) == 0)
		{
			if (!handle_texture(line + 3, &map->so_path))
				return (0);
		}
		else if (ft_strncmp(line, "WE ", 3) == 0)
		{
			if (!handle_texture(line + 3, &map->we_path))
				return (0);
		}
		else if (ft_strncmp(line, "EA ", 3) == 0)
		{
			if (!handle_texture(line + 3, &map->ea_path))
				return (0);
		}
		else if (ft_strncmp(line, "F ", 2) == 0)
		{
			if (!handle_color(line + 2, &map->floor_color))
				return (0);
		}
		else if (ft_strncmp(line, "C ", 2) == 0)
		{
			if (!handle_color(line + 2, &map->ceiling_color))
				return (0);
		}
		
		i++;
	}
	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path || 
		map->floor_color == 0 || map->ceiling_color == 0)
	{
		ft_putstr_fd("Error\nMissing required elements in map file\n", 2);
		return (0);
	}
	return (1);
}