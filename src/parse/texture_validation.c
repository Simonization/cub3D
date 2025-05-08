/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 14:13:18 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parsing_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int is_valid_xpm_path(const char *path)
{
	size_t	len;
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	if (!path)
		return (parsing_error("Texture path is NULL."));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (parsing_error("Texture file must have .xpm extension."));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (parsing_error("Texture file not found or permission denied."));
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (parsing_error("Texture file is empty or unreadable."));
	buffer[bytes_read] = '\0';
	if (ft_strnstr(buffer, "XPM", bytes_read) == NULL && ft_strnstr(buffer, "static char", bytes_read) == NULL)
		return (parsing_error("Invalid XPM file content or format."));
	return (1);
}

static int	assign_texture_path(char **map_texture_path, const char *path_value, int *is_set_flag)
{
	if (*is_set_flag)
		return (parsing_error("Duplicate texture identifier."));
	*map_texture_path = ft_strdup(path_value);
	if (!*map_texture_path)
		return (parsing_error("Memory allocation failed for texture path."));
	if (!is_valid_xpm_path(*map_texture_path))
	{
		free(*map_texture_path);
		*map_texture_path = NULL;
		return (0);
	}
	*is_set_flag = 1;
	return (1);
}

int	parse_texture_and_color_paths(char **lines, t_map *map, int *map_content_start_index)
{
	int		i;
	int		elements_count;
	char	*trimmed_line;
	char	*value_ptr;

	i = 0;
	elements_count = 0;
	map->no_path_set = 0;
	map->so_path_set = 0;
	map->we_path_set = 0;
	map->ea_path_set = 0;
	map->floor_color_set = 0;
	map->ceiling_color_set = 0;
	while (lines[i] && elements_count < 6)
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n");
		if (!trimmed_line)
			return (parsing_error("Memory allocation failed while trimming line."));
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		{
			free(trimmed_line);
			i++;
			continue;
		}
		if (is_map_line(trimmed_line))
		{
			free(trimmed_line);
			break; 
		}
		value_ptr = NULL;
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
			value_ptr = trimmed_line + 3;
		else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
			value_ptr = trimmed_line + 3;
		else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
			value_ptr = trimmed_line + 3;
		else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
			value_ptr = trimmed_line + 3;
		if (value_ptr)
		{
			char *path_candidate = ft_strtrim(value_ptr, " \t");
			if (!path_candidate)
			{
				free(trimmed_line); 
				return parsing_error("Memory alloc failed for path trim.");
			}
			if (ft_strlen(path_candidate) == 0)
			{
				free(path_candidate); free(trimmed_line);
				return parsing_error("Texture path is missing.");
			}
			int success = 0;
			if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
				success = assign_texture_path(&map->no_path, path_candidate, &map->no_path_set);
			else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
				success = assign_texture_path(&map->so_path, path_candidate, &map->so_path_set);
			else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
				success = assign_texture_path(&map->we_path, path_candidate, &map->we_path_set);
			else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
				success = assign_texture_path(&map->ea_path, path_candidate, &map->ea_path_set);
			free(path_candidate);
			if (!success)
			{
				free(trimmed_line);
				return (0);
			}
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			value_ptr = ft_strtrim(trimmed_line + 2, " \t");
			if (!value_ptr)
			{
				free(trimmed_line);
				return parsing_error("Memory alloc for F color trim failed.");
			}
			if (ft_strlen(value_ptr) == 0)
			{
				free(value_ptr);
				free(trimmed_line);
				return parsing_error("Floor color value missing.");
			}
			if (!assign_rgb_color(&map->floor_color, value_ptr, &map->floor_color_set))
				{
					free(value_ptr);
					free(trimmed_line);
					return (0);
				}
			free(value_ptr);
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			value_ptr = ft_strtrim(trimmed_line + 2, " \t");
			if (!value_ptr)
			{
				free(trimmed_line);
				return parsing_error("Memory alloc for C color trim failed.");
			}
			if (ft_strlen(value_ptr) == 0)
			{
				free(value_ptr);
				free(trimmed_line);
				return parsing_error("Ceiling color value missing.");
			}
			if (!assign_rgb_color(&map->ceiling_color, value_ptr, &map->ceiling_color_set))
				{
					free(value_ptr);
					free(trimmed_line);
					return (0);
				}
			free(value_ptr);
			elements_count++;
		}
		else if (trimmed_line[0] != '\0' && !is_map_line(trimmed_line))
		{
			free(trimmed_line);
			return (parsing_error("Invalid identifier or misplaced map content."));
		}
		free(trimmed_line);
		i++;
	}
	*map_content_start_index = i;
	if (!(map->no_path_set && map->so_path_set && map->we_path_set && map->ea_path_set && map->floor_color_set && map->ceiling_color_set))
	{
		return (parsing_error("Incomplete texture/color configuration. All 6 elements (NO, SO, WE, EA, F, C) are required and must be unique."));
	}
	return (1);
}
