/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/07 19:15:11 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_xpm_path(const char *path)
{
    size_t len;

    if (!path)
        return (0);
    len = ft_strlen(path);
    if (len <= 4)
        return (0);
    if (ft_strncmp(path + len - 4, ".xpm", 4) == 0)
        return (1);
    return (0);
}

int	parse_texture_paths(char **lines, t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (lines[i])
	{
		if (ft_strncmp(lines[i], "NO ", 3) == 0 && !map->no_path)
		{
			map->no_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0 && !map->so_path)
		{
			map->so_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0 && !map->we_path)
		{
			map->we_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0 && !map->ea_path)
		{
			map->ea_path = ft_strdup(lines[i] + 3);
			count++;
		}
		else if (ft_strncmp(lines[i], "F ", 2) == 0 && map->floor_color == 0)
		{
			char *value_str = lines[i] + 1;
			while (*value_str && ft_isspace(value_str)) value_str++;
			map->floor_color = parse_and_validate_rgb(value_str);
			if (map->floor_color == -1)
			{
				ft_putstr_fd("Error\nInvalid floor color format or value\n", 2);
				free_array(lines);
				exit(1);
			}
			count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0 && map->ceiling_color == 0)
		{
			char *value_str = lines[i] + 1;
			while (*value_str && ft_isspace(value_str)) value_str++;
			map->ceiling_color = parse_and_validate_rgb(value_str);
			if (map->ceiling_color == -1)
			{
				ft_putstr_fd("Error\nInvalid ceiling color format or value\n", 2);
				free_array(lines);
				exit(1);
			}
			count++;
		}
		i++;
	}
	return (count == 6);
}