/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_gen_cub_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:01:38 by slangero          #+#    #+#             */
/*   Updated: 2025/05/15 21:48:56 by agoldber         ###   ########.fr       */
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
		return (p_err("Texture path is NULL."));
	len = ft_strlen(path);
	if (len <= 4 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (p_err("Texture file must have .xpm extension."));
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (p_err("Texture file not found or permission denied."));
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	close(fd);
	if (bytes_read <= 0)
		return (p_err("Texture file is empty or unreadable."));
	buffer[bytes_read] = '\0';
	if (!(ft_strnstr(buffer, "XPM", bytes_read) != NULL
			&& ft_strnstr(buffer, "static char", bytes_read) != NULL))
		return (p_err("Invalid XPM file content or format."));
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
	line = get_next_line(fd);
	while (1)
	{
		if (!line)
			break ;
		free(line);
		line = get_next_line(fd);
		count++;
	}
	close(fd);
	return (count);
}
