/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:12:42 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 22:12:55 by agoldber         ###   ########.fr       */
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

char	**get_rgb_part(char *rgb_string)
{
	int		i;
	char	**parts;

	i = 0;
	if (!rgb_string)
		return (NULL);
	parts = ft_split(rgb_string, ',');
	if (!parts)
		return (NULL);
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
		return (free_array(parts), NULL);
	return (parts);
}

int	parse_and_validate_rgb(char *rgb_string)
{
	char	**trimmed_parts;
	int		rgb[3];
	int		i;
	int		final_color;
	char	**parts;

	parts = get_rgb_part(rgb_string);
	if (!parts)
		return (-1);
	final_color = -1;
	i = 0;
	trimmed_parts = ft_calloc(4, sizeof(char *));
	while (i < 3)
	{
		trimmed_parts[i] = ft_strtrim(parts[i], " \t\n");
		if (!trimmed_parts[i])
			return (free_array(trimmed_parts), free_array(parts), -1);
		rgb[i] = is_valid_rgb_component(trimmed_parts[i]);
		if (rgb[i] == -1)
			return (free_array(trimmed_parts), free_array(parts), -1);
		i++;
	}
	final_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	return (free_array(trimmed_parts), free_array(parts), final_color);
}
