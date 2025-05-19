/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:44:26 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 21:44:41 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	double_map(char **lines, int j)
{
	while (lines[j])
	{
		if (!ft_isspace(lines[j]))
			return (p_err("Double map."), 1);
		j++;
	}
	return (0);
}

int	fill_map(t_map *map, int j, int map_lines_count, char **lines)
{
	char	*trim;
	int		i;

	i = 0;
	while (i < map_lines_count && lines[j])
	{
		trim = ft_strtrim(lines[j], " \t\n");
		if (!trim)
			return (p_err("Memory allocation failed"), 0);
		if (is_map_line(trim))
		{
			map->map[i] = ft_strdup(lines[j]);
			if (!map->map[i])
				return (free(trim), p_err("Memory allocation failed"), 0);
			i++;
		}
		free(trim);
		j++;
	}
	if (i != map_lines_count)
		return (p_err("Mismatch: counted map VS extracted lines."), 0);
	if (double_map(lines, j))
		return (0);
	return (1);
}
