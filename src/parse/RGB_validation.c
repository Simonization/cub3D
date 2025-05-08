/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:45 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 16:42:36 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_rgb_component(char *component)
{
	int i;
	int value;

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

int parse_and_validate_rgb(char *rgb_string)
{
	char    **parts;
	char    *trimmed_parts[3];
	int     rgb[3];
	int     i;
	int     final_color;

	if (!rgb_string) return (-1);

	parts = ft_split(rgb_string, ',');
	if (!parts) return (-1);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_array(parts);
		return (-1);
	}
	final_color = -1;
	for (i = 0; i < 3; i++)
	{
		trimmed_parts[i] = ft_strtrim(parts[i], " \t\n");
		if (!trimmed_parts[i]) {
			 int k = 0;
			 while(k < i) free(trimmed_parts[k++]);
			 free_array(parts);
			 return -1;
		}
		rgb[i] = is_valid_rgb_component(trimmed_parts[i]);
		free(trimmed_parts[i]);

		if (rgb[i] == -1)
		{
			free_array(parts);
			return (-1);
		}
	}
	final_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	free_array(parts);
	return (final_color);
}

int assign_rgb_color(int *map_color_field, const char *value_str, int *is_set_flag)
{
	char *trimmed_value_str;
	
	if (*is_set_flag)
		return (parsing_error("Duplicate color identifier."));
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
