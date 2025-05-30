/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:11:13 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 21:47:56 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	p_err(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	initialize_map_config_flags(t_map *map)
{
	map->no_path_set = 0;
	map->so_path_set = 0;
	map->we_path_set = 0;
	map->ea_path_set = 0;
	map->floor_color_set = 0;
	map->ceiling_color_set = 0;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
}

char	**read_file_to_array(char *file_path, int line_count)
{
	int		fd;
	int		i;
	char	*line;
	char	**lines;

	lines = malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (free(lines), NULL);
	line = NULL;
	i = 0;
	line = get_next_line(fd);
	while (line && i < line_count)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

t_map	parse_map(char *file_path)
{
	t_map	map;
	char	**lines;
	int		line_count;
	int		map_content_start_index;

	ft_bzero(&map, sizeof(t_map));
	map_content_start_index = 0;
	line_count = count_lines(file_path);
	if (line_count <= 0)
		ft_exit(1, "Failed to read file or empty file", NULL);
	lines = read_file_to_array(file_path, line_count);
	if (!lines)
		ft_exit(1, "Failed to read file lines into array", NULL);
	if (!parse_texture_and_color_paths(lines, &map, &map_content_start_index))
	{
		free_array(lines);
		ft_exit(1, NULL, &map);
	}
	if (!extract_map_data(lines, &map, map_content_start_index))
	{
		free_array(lines);
		ft_exit(1, NULL, &map);
	}
	free_array(lines);
	return (map);
}
