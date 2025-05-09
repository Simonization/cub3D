/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:58:49 by slangero          #+#    #+#             */
/*   Updated: 2025/05/09 19:09:18 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*get_next_line(int fd);
size_t	ftr_strlen(const char *s);
char	*ftr_strchr(const char *s, int c);
char	*ftr_strjoin(char *s1, char const *s2);
char	*ftr_substr(char const *s, unsigned int start, size_t len);

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ftr_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ftr_strjoin(stash, buffer);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	line_len;
	char	*newline_pos;

	if (!stash || stash[0] == '\0')
		return (NULL);
	newline_pos = ftr_strchr(stash, '\n');
	if (newline_pos)
		line_len = (newline_pos - stash) + 1;
	else
		line_len = ftr_strlen(stash);
	line = ftr_substr(stash, 0, line_len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*update_stash(char *stash)
{
	char	*new_stash;
	char	*newline_pos;
	size_t	remaining_len;

	newline_pos = ftr_strchr(stash, '\n');
	if (!newline_pos)
	{
		free(stash);
		return (NULL);
	}
	remaining_len = ftr_strlen(newline_pos + 1);
	new_stash = ftr_substr(stash, (newline_pos - stash) + 1, remaining_len);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = (char *)malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = update_stash(stash);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
