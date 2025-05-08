/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:11:13 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 13:49:23 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		count++;
		free(line);
	}
	close(fd);
	return (count);
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
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < line_count)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		lines[i++] = line;
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
	{
		ft_putstr_fd("Error\nFailed to read file or empty file\n", 2);
		return (map);
	}
	lines = read_file_to_array(file_path, line_count);
	if (!lines)
	{
		ft_putstr_fd("Error\nFailed to read file lines into array\n", 2);
		return (map);
	}
	if (!parse_texture_and_color_paths(lines, &map, &map_content_start_index))
	{
		ft_putstr_fd("Error\nParsing texture and color information failed.\n", 2);
		free_array(lines);
		if (map.no_path)
			free(map.no_path);
		if (map.so_path)
			free(map.so_path);
		if (map.we_path)
			free(map.we_path);
		if (map.ea_path)
			free(map.ea_path);
		ft_bzero(&map, sizeof(t_map));
		return (map);
	}
	if (!extract_map_data(lines, &map, map_content_start_index))
	{
		ft_putstr_fd("Error\nExtracting map data failed.\n", 2);
		free_array(lines);
		if (map.no_path)
			free(map.no_path);
		if (map.so_path)
			free(map.so_path);
		if (map.we_path)
			free(map.we_path);
		if (map.ea_path)
			free(map.ea_path);
		if (map.map) 
			free_array(map.map);
		if (map.line_len) free(map.line_len);
		ft_bzero(&map, sizeof(t_map));
		return (map);
	}
	free_array(lines);
	return (map);
}