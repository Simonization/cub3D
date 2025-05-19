/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:45 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 22:42:30 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_f_color(t_map *map, char *value_part)
{
	char	*rgb_string;

	if (map->floor_color_set)
		return (p_err("Duplicate color identifier: F."));
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
		return (p_err("Memory alloc for F color trim failed."));
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return (p_err("Floor color value missing."));
	}
	if (!assign_rgb_color(&map->floor_color, rgb_string, &map->floor_color_set))
	{
		free(rgb_string);
		return (0);
	}
	free(rgb_string);
	return (1);
}

int	process_c_color(t_map *map, char *value_part)
{
	char	*rgb_string;

	if (map->ceiling_color_set)
		return (p_err("Duplicate color identifier: C."));
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
		return (p_err("Memory alloc for C color trim failed."));
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return (p_err("Ceiling color value missing."));
	}
	if (!assign_rgb_color(&map->ceiling_color,
			rgb_string, &map->ceiling_color_set))
	{
		free(rgb_string);
		return (0);
	}
	free(rgb_string);
	return (1);
}

int	assign_rgb_color(int *field,
						const char *value_str, int *is_set_flag)
{
	char	*trimmed_value_str;

	trimmed_value_str = ft_strtrim(value_str, " \t");
	if (!trimmed_value_str)
		return (p_err("Memory allocation failed for color string."));
	*field = parse_and_validate_rgb(trimmed_value_str);
	free(trimmed_value_str);
	if (*field == -1)
		return (p_err("Invalid RGB color format or value."));
	*is_set_flag = 1;
	return (1);
}
