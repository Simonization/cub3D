/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 13:12:16 by slangero         ###   ########.fr       */
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

/**
 * @brief Validates a single XPM texture path.
 *
 * Checks:
 * 1. Path is not NULL.
 * 2. Path has a ".xpm" extension.
 * 3. File exists and is readable.
 * 4. (Simplified) File is not empty and contains "XPM".
 *
 * @param path The file path to the XPM texture.
 * @return int 1 if valid, 0 otherwise (error message printed to stderr).
 */
int is_valid_xpm_path(const char *path)
{
	size_t	len;
	int		fd;
	char	buffer[256]; // Read a small chunk to check for "XPM"
	ssize_t	bytes_read;

	if (!path)
		return (parsing_error("Texture path is NULL."));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		// Construct a more specific message if desired for debugging
		// char err_msg[100]; snprintf(err_msg, 100, "Texture file '%s' must have .xpm extension.", path);
		// return (parsing_error(err_msg));
		return (parsing_error("Texture file must have .xpm extension."));
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		// char err_msg[100]; snprintf(err_msg, 100, "Cannot open texture file: %s", path);
		// return (parsing_error(err_msg));
		return (parsing_error("Texture file not found or permission denied."));
	}

	// Read a small portion of the file to check for "XPM"
	// This is a basic check; mlx_xpm_file_to_image will do the full validation.
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd); // Close the file descriptor once done

	if (bytes_read <= 0) // Error reading or empty file
	{
		// char err_msg[100]; snprintf(err_msg, 100, "Texture file is empty or unreadable: %s", path);
		// return (parsing_error(err_msg));
		return (parsing_error("Texture file is empty or unreadable."));
	}
	buffer[bytes_read] = '\0'; // Null-terminate the buffer

	// Check if "XPM" (part of "/* XPM */") or "static char" (for C array style) is present
	// This makes it more flexible for both raw XPM and XPMs defined as C arrays.
	if (ft_strnstr(buffer, "XPM", bytes_read) == NULL && ft_strnstr(buffer, "static char", bytes_read) == NULL)
	{
		// char err_msg[100]; snprintf(err_msg, 100, "Invalid XPM content (missing 'XPM' or 'static char' in header): %s", path);
		// return (parsing_error(err_msg));
		return (parsing_error("Invalid XPM file content or format."));
	}

	// The ultimate test will be mlx_xpm_file_to_image.
	// This function just does preliminary checks.
	return (1); // Valid for parsing purposes
}

// ... (rest of your texture_validation.c file: assign_texture_path, assign_rgb_color, parse_texture_and_color_paths)
// Make sure assign_texture_path correctly calls this new is_valid_xpm_path

static int	assign_texture_path(char **map_texture_path, const char *path_value, int *is_set_flag)
{
	if (*is_set_flag)
		return (parsing_error("Duplicate texture identifier.")); // Keep this check

	// Free previous path if any (though with is_set_flag, this shouldn't be needed unless re-parsing)
	// if (*map_texture_path) {
	// 	free(*map_texture_path);
	// 	*map_texture_path = NULL;
	// }
	
	*map_texture_path = ft_strdup(path_value);
	if (!*map_texture_path)
		return (parsing_error("Memory allocation failed for texture path."));

	if (!is_valid_xpm_path(*map_texture_path)) // Calls the updated validator
	{
		free(*map_texture_path);
		*map_texture_path = NULL;
		// is_valid_xpm_path already printed its specific error
		return (0); // Return 0 to indicate failure
	}
	*is_set_flag = 1;
	return (1);
}

// The rest of your texture_validation.c file (assign_rgb_color, parse_texture_and_color_paths)
// should remain largely the same, assuming they correctly call assign_texture_path.
// The definition of parse_texture_and_color_paths itself is correct based on your plan and previous step.

// ... (assign_rgb_color and parse_texture_and_color_paths from your file)
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
	// Initialize flags to 0 (not set)
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
		// Ensure there's a space after the identifier
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
			char *path_candidate = ft_strtrim(value_ptr, " \t"); // Trim the path itself
			if (!path_candidate) { free(trimmed_line); return parsing_error("Memory alloc failed for path trim.");}
			if (ft_strlen(path_candidate) == 0) { // Check for empty path after identifier
				free(path_candidate); free(trimmed_line); return parsing_error("Texture path is missing.");
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
			if (!success) { free(trimmed_line); return (0); } // assign_texture_path or parsing_error would have printed
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
		{
			value_ptr = ft_strtrim(trimmed_line + 2, " \t"); // Trim the RGB string
			if (!value_ptr) { free(trimmed_line); return parsing_error("Memory alloc for F color trim failed.");}
			if (ft_strlen(value_ptr) == 0) { free(value_ptr); free(trimmed_line); return parsing_error("Floor color value missing.");}
			if (!assign_rgb_color(&map->floor_color, value_ptr, &map->floor_color_set))
				{ free(value_ptr); free(trimmed_line); return (0); } // assign_rgb_color or parsing_error printed
			free(value_ptr);
			elements_count++;
		}
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
		{
			value_ptr = ft_strtrim(trimmed_line + 2, " \t"); // Trim the RGB string
			if (!value_ptr) { free(trimmed_line); return parsing_error("Memory alloc for C color trim failed.");}
			if (ft_strlen(value_ptr) == 0) { free(value_ptr); free(trimmed_line); return parsing_error("Ceiling color value missing.");}
			if (!assign_rgb_color(&map->ceiling_color, value_ptr, &map->ceiling_color_set))
				{ free(value_ptr); free(trimmed_line); return (0); } // assign_rgb_color or parsing_error printed
			free(value_ptr);
			elements_count++;
		}
		else if (trimmed_line[0] != '\0' && !is_map_line(trimmed_line)) // Non-empty, not texture/color, not map
		{
			// More specific error: what was it?
			// char err_msg[100]; snprintf(err_msg, 100, "Invalid identifier or misplaced content: '%s'", trimmed_line);
			// free(trimmed_line);
			// return (parsing_error(err_msg));
			free(trimmed_line);
			return (parsing_error("Invalid identifier or misplaced map content."));
		}
		free(trimmed_line);
		i++;
	}
	*map_content_start_index = i; // Save where we stopped parsing elements
	
	// Check if all 6 elements were found and set
	if (!(map->no_path_set && map->so_path_set && map->we_path_set && map->ea_path_set && map->floor_color_set && map->ceiling_color_set))
	{
	    // You can add more specific messages here if you want to know WHICH element is missing
	    // For example: if (!map->no_path_set) parsing_error("NO texture path missing."); ...etc.
		return (parsing_error("Incomplete texture/color configuration. All 6 elements (NO, SO, WE, EA, F, C) are required and must be unique."));
	}
	return (1); // Success
}
