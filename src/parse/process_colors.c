/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:49:43 by slangero          #+#    #+#             */
/*   Updated: 2025/05/12 20:49:45 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_f_color(t_map *map, char *value_part)
{
	char	*rgb_string;

	if (map->floor_color_set)
	{
		return (parsing_error("Duplicate color identifier: F."));
	}
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
	{
		return (parsing_error("Memory alloc for F color trim failed."));
	}
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return (parsing_error("Floor color value missing."));
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
	{
		return (parsing_error("Duplicate color identifier: C."));
	}
	rgb_string = ft_strtrim(value_part, " \t");
	if (!rgb_string)
	{
		return (parsing_error("Memory alloc for C color trim failed."));
	}
	if (ft_strlen(rgb_string) == 0)
	{
		free(rgb_string);
		return (parsing_error("Ceiling color value missing."));
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