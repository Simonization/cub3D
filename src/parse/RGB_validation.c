/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:45 by slangero          #+#    #+#             */
/*   Updated: 2025/05/09 13:42:32 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int process_f_color(t_map *map, char *value_part)
{
	char *rgb_string;

	if (map->floor_color_set)
	{
		return (parsing_error("Duplicate color identifier: F."));
	}
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
	{
		return parsing_error("Memory alloc for F color trim failed.");
	}
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return parsing_error("Floor color value missing.");
	}
	if (!assign_rgb_color(&map->floor_color, rgb_string, &map->floor_color_set))
	{
		free(rgb_string);
		return (0);
	}
	free(rgb_string);
	return (1);
}

int process_c_color(t_map *map, char *value_part)
{
	char *rgb_string;

	if (map->ceiling_color_set)
	{
		return (parsing_error("Duplicate color identifier: C."));
	}
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
	{
		return parsing_error("Memory alloc for C color trim failed.");
	}
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return parsing_error("Ceiling color value missing.");
	}
	if (!assign_rgb_color(&map->ceiling_color, rgb_string, &map->ceiling_color_set))
	{
		free(rgb_string);
		return (0);
	}
	free(rgb_string);
	return (1);
}

int	is_valid_rgb_component(char *component)
{
	int	i;
	int	value;

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

int	parse_and_validate_rgb(char *rgb_string)
{
	char	*trimmed_parts[3];
	int		rgb[3];
	int		i;
	int		final_color;
	int		k;
	char	**parts;

	if (!rgb_string)
		return (-1);
	parts = ft_split(rgb_string, ',');
	if (!parts)
		return (-1);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_array(parts);
		return (-1);
	}
	final_color = -1;
	i = 0;
	while (i < 3)
	{
		trimmed_parts[i] = ft_strtrim(parts[i], " \t\n");
		if (!trimmed_parts[i])
		{
			k = 0;
			while (k < i)
			{
				free(trimmed_parts[k++]);
				free_array(parts);
			}
			return (-1);
		}
		rgb[i] = is_valid_rgb_component(trimmed_parts[i]);
		free(trimmed_parts[i]);
		if (rgb[i] == -1)
		{
			free_array(parts);
			return (-1);
		}
		i++;
	}
	final_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_array(parts);
	return (final_color);
}

int assign_rgb_color(int *map_color_field, const char *value_str, int *is_set_flag)
{
	char *trimmed_value_str;
	
	trimmed_value_str = ft_strtrim(value_str, " \t");
	if (!trimmed_value_str)
		return (parsing_error("Memory allocation failed for color string.")); // This error is fine

	*map_color_field = parse_and_validate_rgb(trimmed_value_str);
	free(trimmed_value_str);

	if (*map_color_field == -1)
		return (parsing_error("Invalid RGB color format or value.")); // This error is fine
	
	*is_set_flag = 1;
	return (1);
}
