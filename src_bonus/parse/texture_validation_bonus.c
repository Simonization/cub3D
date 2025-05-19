/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:09:05 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 22:44:18 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	assign_texture_path(char **path,
		const char *path_value, int *is_set)
{
	if (*is_set)
		return (p_err("Duplicate texture identifier."));
	*path = ft_strdup(path_value);
	if (!*path)
		return (p_err("Memory allocation failed for texture path."));
	if (!is_valid_xpm_path(*path))
	{
		free(*path);
		*path = NULL;
		return (0);
	}
	*is_set = 1;
	return (1);
}

int	get_texture_path(char *trimmed_line, t_map *map, int *elements_count)
{
	int	success_flag;

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
		return (free(trimmed_line), p_err(
				"Invalid identifier or misplaced map content."));
	free(trimmed_line);
	if (success_flag == 0 && *elements_count < 6)
		return (0);
	if (success_flag == 1)
		(*elements_count)++;
	return (1);
}

int	check_trim(char **lines, char *trim, char *c)
{
	if (!trim)
	{
		free_array(lines);
		ft_exit(1, "Memory allocation failed", NULL);
	}
	if (trim[0] == '\0' || trim[0] == '#' || is_map_line(trim))
	{
		*c = trim[0];
		free(trim);
		return (1);
	}
	return (0);
}

int	parse_texture_and_color_paths(
		char **lines, t_map *map, int *start)
{
	int		i;
	int		elements_count;
	char	*trimmed_line;
	char	c;

	i = -1;
	elements_count = 0;
	while (lines[++i] && elements_count < 6)
	{
		trimmed_line = ft_strtrim(lines[i], " \t\n");
		if (check_trim(lines, trimmed_line, &c))
		{
			if (c == '\0' || c == '#')
				continue ;
			break ;
		}
		if (!get_texture_path(trimmed_line, map, &elements_count))
			return (0);
	}
	*start = i;
	if (elements_count < 6)
		return (p_err(
				"Incomplete texture/color. Need 6 elements."));
	return (1);
}
