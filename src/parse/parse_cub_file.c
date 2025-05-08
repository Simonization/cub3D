/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:11:13 by slangero          #+#    #+#             */
/*   Updated: 2025/05/08 12:39:32 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *file_path)
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

static char	**read_file_to_array(char *file_path, int line_count)
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

	ft_bzero(&map, sizeof(t_map));
	line_count = count_lines(file_path);
	if (line_count <= 0)
	{
		ft_putstr_fd("Error\nFailed to read file or empty file\n", 2);
		return (map);
	}
	lines = read_file_to_array(file_path, line_count);
	if (!lines)
	{
		ft_putstr_fd("Error\nFailed to read file\n", 2);
		return (map);
	}

	if (!parse_texture_paths(lines, &map, ))
	{
		ft_putstr_fd("Error\nInvalid or missing texture/color information\n", 2);
		free_array(lines);
		return (map);
	}

	if (!extract_map_data(lines, &map))
	{
		ft_putstr_fd("Error\nInvalid map data\n", 2);
		free_array(lines);
		return (map);
	}

	free_array(lines);
	return (map);
}