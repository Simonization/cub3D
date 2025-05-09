/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/09 13:54:36 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_texture_path(char **map_texture_path, const char *path_value, int *is_set_flag)
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
	int		success_flag;

	i = 0;
	elements_count = 0;
	while (lines[i] && elements_count < 6)
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n");
		if (!trimmed_line)
			return (parsing_error("Memory allocation failed while trimming line."));
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
		{
			free(trimmed_line);
			i++;
			continue ;
		}
		if (is_map_line(trimmed_line))
		{
			free(trimmed_line);
			break ;
		}
		success_flag = 0;
		if (ft_strncmp(trimmed_line, "NO ", 3) == 0)
			success_flag = process_no_texture(map, trimmed_line + 3);
		else if (ft_strncmp(trimmed_line, "SO ", 3) == 0)
			success_flag = process_so_texture(map, trimmed_line + 3);
		else if (ft_strncmp(trimmed_line, "WE ", 3) == 0)
			success_flag = process_we_texture(map, trimmed_line + 3);
		else if (ft_strncmp(trimmed_line, "EA ", 3) == 0)
			success_flag = process_ea_texture(map, trimmed_line + 3);
		else if (ft_strncmp(trimmed_line, "F ", 2) == 0)
			success_flag = process_f_color(map, trimmed_line + 2);
		else if (ft_strncmp(trimmed_line, "C ", 2) == 0)
			success_flag = process_c_color(map, trimmed_line + 2);
		else if (trimmed_line[0] != '\0' && !is_map_line(trimmed_line))
		{
			free(trimmed_line);
			return (parsing_error("Invalid identifier or misplaced map content."));
		}
		free(trimmed_line);
		if (success_flag == 0 && elements_count < 6)
			return (0);
		if (success_flag == 1)
			elements_count++;
		i++;
	}
	*map_content_start_index = i;
	if (elements_count < 6)
	{
		return (parsing_error(
				"Incomplete texture/color configuration. 6 elements required."));
	}
	return (1);
}
