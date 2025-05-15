/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:45 by slangero          #+#    #+#             */
/*   Updated: 2025/05/12 20:49:56 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static char	**split_and_validate_rgb_string(char *rgb_string)
{
	char	**parts;
	int		i;

	if (!rgb_string)
		return (NULL);
	parts = ft_split(rgb_string, ',');
	if (!parts)
		return (NULL);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_array(parts);
		return (NULL);
	}
	return (parts);
}

static int	extract_rgb_values_from_parts(char **parts, int rgb_values[3])
{
	int		i;
	char	*trimmed_component;

	i = 0;
	while (i < 3)
	{
		trimmed_component = ft_strtrim(parts[i], " \t\n");
		if (!trimmed_component)
			return (0);
		rgb_values[i] = is_valid_rgb_component(trimmed_component);
		free(trimmed_component);
		if (rgb_values[i] == -1)
			return (0);
	}
	return (1);
}

int	parse_and_validate_rgb(char *rgb_string)
{
	char	**parts;
	int		rgb[3];
	int		final_color;

	parts = split_and_validate_rgb_string(rgb_string);
	if (!parts)
		return (-1);
	if (!extract_rgb_values_from_parts(parts, rgb))
	{
		free_array(parts);
		return (-1);
	}
	final_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_array(parts);
	return (final_color);
}

int	assign_rgb_color(int *map_color_field,
						const char *value_str, int *is_set_flag)
{
	char	*trimmed_value_str;

	trimmed_value_str = ft_strtrim(value_str, " \t");
	if (!trimmed_value_str)
		return (parsing_error("Memory allocation failed for color string."));
	*map_color_field = parse_and_validate_rgb(trimmed_value_str);
	free(trimmed_value_str);
	if (*map_color_field == -1)
		return (parsing_error("Invalid RGB color format or value."));
	*is_set_flag = 1;
	return (1);
}
