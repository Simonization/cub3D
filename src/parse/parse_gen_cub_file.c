/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gen_cub_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:01:38 by slangero          #+#    #+#             */
/*   Updated: 2025/05/09 13:02:08 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_xpm_path(const char *path)
{
	size_t	len;
	int		fd;
	char	buffer[256];
	ssize_t	bytes_read;

	if (!path)
		return (parsing_error("Texture path is NULL."));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (parsing_error("Texture file must have .xpm extension."));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (parsing_error("Texture file not found or permission denied."));
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (parsing_error("Texture file is empty or unreadable."));
	buffer[bytes_read] = '\0';
	if (!(ft_strnstr(buffer, "XPM", bytes_read) != NULL \
		&& ft_strnstr(buffer, "static char", bytes_read) != NULL))
		return (parsing_error("Invalid XPM file content or format."));
	return (1);
}

int	count_lines(char *file_path)
{
	int		fd;
	int		count;
	char	*line;

	line = 0;
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