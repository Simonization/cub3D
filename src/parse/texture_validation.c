/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 12:20:16 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// Canvas for src/parse/texture_validation.c
#include "cub3d.h" // Should include libft.h, fcntl.h, unistd.h indirectly or directly
#include <fcntl.h>  // For open, close
#include <unistd.h> // For read

// Centralized error message function for parsing non-map elements.
// Returns 0 to indicate failure, simplifying error checking in callers.
static int parsing_error(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2); // Cast to char* if msg is const
	ft_putstr_fd("\n", 2);
	return (0);
}

/**
 * @brief Validates a single XPM texture path.
 *
 * Checks:
 * 1. Path is not NULL.
 * 2. Path has a ".xpm" extension.
 * 3. File exists and is readable.
 * 4. File is not empty and starts with the "XPM " header.
 *
 * @param path The file path to the XPM texture.
 * @return int 1 if valid, 0 otherwise (error message printed to stderr).
 */
int is_valid_xpm_path(const char *path)
{
	size_t	len;
	int		fd;
	char	*line_xpm; // For reading the header

	if (!path)
		return (parsing_error("Texture path is NULL."));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (parsing_error("Texture file must have .xpm extension."));
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		// Construct a more specific error message if desired
		// For example: char err_msg[1024]; snprintf(err_msg, sizeof(err_msg), "Cannot open texture file: %s", path);
		return (parsing_error("Texture file not found or permission denied."));
	}
	line_xpm = get_next_line(fd); // Make sure get_next_line is in your project
	if (!line_xpm)
	{
		close(fd);
		return (parsing_error("Texture file is empty or unreadable."));
	}
	if (ft_strncmp(line_xpm, "/* XPM */", 8) != 0)
	{
		free(line_xpm);
		close(fd);
		return (parsing_error("Invalid XPM file header."));
	}
	free(line_xpm);
	// It's good practice to read a bit more to ensure it's not just the header
	// but for this project, the header check is often deemed sufficient.
	close(fd);
	return (1); // Valid
}

static int	assign_texture_path(char **map_texture_path, const char *path_value, int *is_set_flag)
{
	if (*is_set_flag)
		return (parsing_error("Duplicate texture/color identifier."));

	*map_texture_path = ft_strdup(path_value);
	if (!*map_texture_path)
		return (parsing_error("Memory allocation failed for texture path."));

	if (!is_valid_xpm_path(*map_texture_path))
	{
		free(*map_texture_path);
		*map_texture_path = NULL;
		// is_valid_xpm_path already printed its specific error
		return (0);
	}
	*is_set_flag = 1;
	return (1);
}

static int assign_rgb_color(int *map_color_field, const char *value_str, int *is_set_flag)
{
	char *trimmed_value_str;
	
	if (*is_set_flag)
		return (parsing_error("Duplicate color identifier."));

	trimmed_value_str = ft_strtrim(value_str, " \t");
	if (!trimmed_value_str)
		return (parsing_error("Memory allocation failed for color string."));

	*map_color_field = parse_and_validate_rgb(trimmed_value_str); // This function is from RGB_validation.c
	free(trimmed_value_str);

	if (*map_color_field == -1)
	{
		// parse_and_validate_rgb or a wrapper should print specific RGB error
		return (parsing_error("Invalid RGB color format or value."));
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
	while (lines[i] && elements_count < 6)
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n");
		if (!trimmed_line)
			return (parsing_error("Memory allocation failed while trimming line."));
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#') // Skip empty or comment lines
		{
			free(trimmed_line);
			i++;
			continue;
		}
		// Check for map lines to stop texture/color parsing
		if (is_map_line(trimmed_line)) // is_map_line needs to correctly identify start of map
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
		
		if (value_ptr) // It's a texture
		{
			char *path_candidate = ft_strtrim(value_ptr, " \t");
			if (!path_candidate) { free(trimmed_line); return parsing_error("Memory alloc failed for path trim.");}

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
			if (!success) { free(trimmed_line); return (0); }
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			if (!assign_rgb_color(&map->floor_color, trimmed_line + 2, &map->floor_color_set))
				{ free(trimmed_line); return (0); }
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			if (!assign_rgb_color(&map->ceiling_color, trimmed_line + 2, &map->ceiling_color_set))
				{ free(trimmed_line); return (0); }
			elements_count++;
		}
		else if (trimmed_line[0] != '\0' && !is_map_line(trimmed_line)) // Non-empty, not texture/color, not map
		{
			free(trimmed_line);
			return (parsing_error("Invalid identifier or misplaced map line."));
		}
		free(trimmed_line);
		i++;
	}
	*map_content_start_index = i; // Save where we stopped parsing elements
	if (elements_count != 6)
		return (parsing_error("Incomplete texture/color configuration. All 6 elements are required."));
	return (1); // Success
}


// int is_valid_xpm_path(const char *path)
// {
//     size_t len;

//     if (!path)
//         return (0);
//     len = ft_strlen(path);
//     if (len <= 4)
//         return (0);
//     if (ft_strncmp(path + len - 4, ".xpm", 4) == 0)
//         return (1);
//     return (0);
// }

// int	parse_texture_paths(char **lines, t_map *map)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (lines[i])
// 	{
// 		if (ft_strncmp(lines[i], "NO ", 3) == 0 && !map->no_path)
// 		{
// 			map->no_path = ft_strdup(lines[i] + 3);
// 			count++;
// 		}
// 		else if (ft_strncmp(lines[i], "SO ", 3) == 0 && !map->so_path)
// 		{
// 			map->so_path = ft_strdup(lines[i] + 3);
// 			count++;
// 		}
// 		else if (ft_strncmp(lines[i], "WE ", 3) == 0 && !map->we_path)
// 		{
// 			map->we_path = ft_strdup(lines[i] + 3);
// 			count++;
// 		}
// 		else if (ft_strncmp(lines[i], "EA ", 3) == 0 && !map->ea_path)
// 		{
// 			map->ea_path = ft_strdup(lines[i] + 3);
// 			count++;
// 		}
// 		else if (ft_strncmp(lines[i], "F ", 2) == 0 && map->floor_color == 0)
// 		{
// 			char *value_str = lines[i] + 1;
// 			while (*value_str && ft_isspace(value_str)) value_str++;
// 			map->floor_color = parse_and_validate_rgb(value_str);
// 			if (map->floor_color == -1)
// 			{
// 				ft_putstr_fd("Error\nInvalid floor color format or value\n", 2);
// 				free_array(lines);
// 				exit(1);
// 			}
// 			count++;
// 		}
// 		else if (ft_strncmp(lines[i], "C ", 2) == 0 && map->ceiling_color == 0)
// 		{
// 			char *value_str = lines[i] + 1;
// 			while (*value_str && ft_isspace(value_str)) value_str++;
// 			map->ceiling_color = parse_and_validate_rgb(value_str);
// 			if (map->ceiling_color == -1)
// 			{
// 				ft_putstr_fd("Error\nInvalid ceiling color format or value\n", 2);
// 				free_array(lines);
// 				exit(1);
// 			}
// 			count++;
// 		}
// 		i++;
// 	}
// 	return (count == 6);
// }