/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:25:33 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 13:14:29 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// is_map_line remains the same, it's a helper to identify map lines.
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	// Skip leading whitespace
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	
	// If line is empty after skipping whitespace, it's not a map line for content purposes here
	if (!line[i]) 
		return (0); 
		
	// Check if the first non-whitespace character is valid for a map line start
	// This helps distinguish from config lines like "NO ./path"
	if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		return (0); // Not starting with a map character.

	// Now validate the rest of the characters on this line
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' && line[i] != '\t' &&
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && 
			line[i] != 'W')
			return (0); // Invalid character found
		i++;
	}
	return (1); // Line consists only of valid map characters and whitespace
}

// find_map_start is now effectively replaced by map_content_start_index
// but we can keep a similar logic if needed, starting from the given index.
// For now, extract_map_data will directly use map_content_start_index.

static int	count_map_lines(char **lines, int start_idx)
{
	int	i;
	int	count;
	int	found_map_content; // To correctly handle empty lines between map blocks if any

	i = start_idx;
	count = 0;
	found_map_content = 0;

	while (lines[i])
	{
		char *trimmed_line = ft_strtrim(lines[i], " \t\n"); // Trim for accurate check
		if (!trimmed_line) {
			// Malloc error, critical
			ft_putstr_fd("Error: Malloc failed in count_map_lines\n", 2);
			return -1; // Indicate error
		}

		if (is_map_line(trimmed_line)) // Use the robust is_map_line
		{
			count++;
			found_map_content = 1;
		}
		else if (trimmed_line[0] == '\0' && found_map_content) 
		{
			// An empty line after some map content has been found.
			// This could signify the end of the map block or an invalid empty line within the map.
			// For now, we'll assume it marks the end of the current map block.
			// More robust parsing might check for subsequent map lines to detect invalid internal empty lines.
			free(trimmed_line);
			break; 
		}
		else if (found_map_content)
		{
			// Non-map line, non-empty line after map content started: end of map
			free(trimmed_line);
			break;
		}
		// If !is_map_line and !found_map_content, it's a non-map line before the map (e.g. empty line or leftover config)
		// These are skipped by the logic in parse_texture_and_color_paths which gives us start_idx.
		
		free(trimmed_line);
		i++;
	}
	return (count);
}

// extract_map_data now takes map_content_start_index
int	extract_map_data(char **lines, t_map *map, int map_content_start_index)
{
	int	map_actual_start_line_idx; // The true first line of map content
	int	map_lines_count;
	int	i; // Loop counter for filling map->map
	int	j; // Loop counter for iterating through lines array

	// Find the actual first line of the map, skipping any blank lines
	// that might exist after texture/color definitions but before the map.
	map_actual_start_line_idx = map_content_start_index;
	while(lines[map_actual_start_line_idx])
	{
		char *trimmed_line = ft_strtrim(lines[map_actual_start_line_idx], " \t\n");
		if (!trimmed_line) {
			ft_putstr_fd("Error: Malloc failed in extract_map_data (trimming for start find)\n", 2);
			return 0; // Malloc error
		}
		int is_map = is_map_line(trimmed_line);
		free(trimmed_line);
		if (is_map) {
			break; // Found the first actual map line
		}
		map_actual_start_line_idx++; // Move to next line
	}

	if (!lines[map_actual_start_line_idx]) {
		ft_putstr_fd("Error\nNo map content found after texture/color definitions.\n", 2);
		return (0); // No map lines found at or after map_content_start_index
	}
		
	map_lines_count = count_map_lines(lines, map_actual_start_line_idx);
	if (map_lines_count <= 0) // count_map_lines returns -1 on malloc error
	{
		ft_putstr_fd("Error\nNo valid map lines found or error in counting.\n", 2);
		return (0);
	}
		
	map->map = malloc(sizeof(char *) * (map_lines_count + 1));
	// Allocate line_len with calloc for zero-initialization, good practice
	map->line_len = ft_calloc(map_lines_count + 1, sizeof(int)); 
	if (!map->map || !map->line_len)
	{
		ft_putstr_fd("Error\nMalloc failed for map structure.\n", 2);
		free(map->map); // free if one succeeded and other failed
		free(map->line_len);
		map->map = NULL; map->line_len = NULL; // Set to NULL after freeing
		return (0);
	}
	
	map->map_height = map_lines_count; // Store map height
	map->map_width = 0; // Initialize map_width, will find max later

	i = 0;
	j = map_actual_start_line_idx;
	// Iterate only for the number of lines identified as part of the map
	while (i < map_lines_count && lines[j]) 
	{
		// We should only process lines that are confirmed to be map lines
		// count_map_lines should ensure we only count actual map lines.
		// This check here is a safeguard or if count_map_lines logic changes.
		char *current_line_trimmed = ft_strtrim(lines[j], " \t\n"); // Trim for is_map_line check
		if (!current_line_trimmed) { /* Malloc error */ free_array(map->map); free(map->line_len); map->map = NULL; map->line_len = NULL; return 0; }

		if (is_map_line(current_line_trimmed))
		{
			// Duplicate the original line from lines[j], not the trimmed one, to preserve original spacing if intended for map structure.
			// However, for map validation, often trailing/leading spaces per line are not significant,
			// but spaces *within* the line are.
			// For cub3D, it's common to use the raw line.
			map->map[i] = ft_strdup(lines[j]);
			if (!map->map[i])
			{
				free_array(map->map); // map->map[i] is NULL, so free_array handles it
				free(map->line_len);
				map->map = NULL; map->line_len = NULL;
				free(current_line_trimmed);
				return (0); // Malloc error
			}
			map->line_len[i] = ft_strlen(map->map[i]);
			if (map->line_len[i] > map->map_width) // Update max width
				map->map_width = map->line_len[i];
			i++;
		}
		// If it's not a map line but we are in the map block (based on count_map_lines logic),
		// this implies an empty line or invalid line breaking the map block, which count_map_lines should handle.
		free(current_line_trimmed);
		j++;
		if (i == map_lines_count && lines[j] && is_map_line(ft_strtrim(lines[j], " \t\n"))) {
			// This means there's more map content after what count_map_lines determined.
			// This indicates a possible issue with map formatting (e.g. disjointed map blocks).
			ft_putstr_fd("Error\nMap content seems disjointed or invalid empty lines within map.\n", 2);
			free_array(map->map); free(map->line_len); map->map = NULL; map->line_len = NULL;
			return (0);
		}
	}
	map->map[i] = NULL; // Null-terminate the array of map lines
	
	if (i != map_lines_count) {
		// This case should ideally not be hit if count_map_lines is accurate
		// and lines array is consistent.
		ft_putstr_fd("Error\nMismatch between counted map lines and extracted lines.\n", 2);
		free_array(map->map); free(map->line_len); map->map = NULL; map->line_len = NULL;
		return (0);
	}
	return (1); // Success
}