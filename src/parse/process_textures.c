/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:39:43 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 17:01:53 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_no_texture(t_map *map, char *value_part)
{
	char	*path_candidate;

	if (map->no_path_set)
		return (p_err("Duplicate texture identifier: NO."));
	path_candidate = ft_strtrim(value_part, " \t");
	if (!path_candidate)
		return (p_err("Memory alloc failed for NO path trim."));
	if (ft_strlen(path_candidate) == 0)
	{
		free(path_candidate);
		return (p_err("Texture path is missing for NO."));
	}
	if (!assign_texture_path(&map->no_path, path_candidate, &map->no_path_set))
		return (free(path_candidate), 0);
	free(path_candidate);
	return (1);
}

int	process_so_texture(t_map *map, char *value_part)
{
	char	*path_candidate;

	if (map->so_path_set)
		return (p_err("Duplicate texture identifier: SO."));
	path_candidate = ft_strtrim(value_part, " \t");
	if (!path_candidate)
		return (p_err("Memory alloc failed for SO path trim."));
	if (ft_strlen(path_candidate) == 0)
	{
		free(path_candidate);
		return (p_err("Texture path is missing for SO."));
	}
	if (!assign_texture_path(&map->so_path, path_candidate, &map->so_path_set))
		return (free(path_candidate), 0);
	free(path_candidate);
	return (1);
}

int	process_we_texture(t_map *map, char *value_part)
{
	char	*path_candidate;

	if (map->we_path_set)
		return (p_err("Duplicate texture identifier: WE."));
	path_candidate = ft_strtrim(value_part, " \t");
	if (!path_candidate)
		return (p_err("Memory alloc failed for WE path trim."));
	if (ft_strlen(path_candidate) == 0)
	{
		free(path_candidate);
		return (p_err("Texture path is missing for WE."));
	}
	if (!assign_texture_path(&map->we_path, path_candidate, &map->we_path_set))
		return (free(path_candidate), 0);
	free(path_candidate);
	return (1);
}

int	process_ea_texture(t_map *map, char *value_part)
{
	char	*path_candidate;

	if (map->ea_path_set)
		return (p_err("Duplicate texture identifier: EA."));
	path_candidate = ft_strtrim(value_part, " \t");
	if (!path_candidate)
		return (p_err("Memory alloc failed for EA path trim."));
	if (ft_strlen(path_candidate) == 0)
	{
		free(path_candidate);
		return (p_err("Texture path is missing for EA."));
	}
	if (!assign_texture_path(&map->ea_path, path_candidate, &map->ea_path_set))
		return (free(path_candidate), 0);
	free(path_candidate);
	return (1);
}
