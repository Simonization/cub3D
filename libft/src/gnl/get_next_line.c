/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:58:49 by slangero          #+#    #+#             */
/*   Updated: 2025/05/12 19:25:03 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define DELIMITER '\n'

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif 

char	*read_line(int fd, char *stash, char *buffer);
char	*ftr_strchr(char *s);


char	*ftr_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == '\n')
		return ((char *)&s[i]);
	return (NULL);
}

int	ftr_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ftr_strdup(char *s)
{
	char				*dupstr;
	unsigned int		i;

	if (!s)
		return (NULL);
	dupstr = malloc(sizeof(char) * (ftr_strlen(s) + 1));
	if (!dupstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dupstr[i] = s[i];
		i++;
	}
	dupstr[i] = '\0';
	return (dupstr);
}

char	*ftr_substr(char *s, int start, int len)
{
	char	*substr;
	int		i;

	if (!s)
		return (NULL);
	if (start > ftr_strlen(s))
		return (malloc(1));
	if (len > ftr_strlen(s + start))
		len = ftr_strlen(s + start);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}

char	*ftr_strjoin(char *str, char *buff)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc((ftr_strlen(str) + ftr_strlen(buff) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (str && str[j])
		res[i++] = str[j++];
	j = 0;
	while (buff[j])
		res[i++] = buff[j++];
	res[i] = '\0';
	return (res);
}

char	*ftr_free(char **str, int n)
{
	if (n)
		free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_extract_line(char **line_buffer)
{
	int		i;
	char	*decat;
	char	*temp;

	i = 0;
	temp = *line_buffer;
	while (temp[i] != '\n' && temp[i] != '\0')
		i++;
	if (temp[i] == 0 || temp[1] == 0)
		return (NULL);
	decat = ftr_substr(*line_buffer, i + 1, ftr_strlen(temp) - i);
	if (!decat)
		return (NULL);
	if (*decat == 0)
		ftr_free(&decat, 1);
	temp[i + 1] = 0;
	*line_buffer = ftr_substr(temp, 0, i + 1);
	free(temp);
	if (!*line_buffer)
		return (ftr_free(&decat, 1));
	return (decat);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*stash;

	if (BUFFER_SIZE >= INT_MAX)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (ftr_free(&stash, 1));
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ftr_free(&stash, 1));
	line = read_line(fd, stash, buffer);
	free(buffer);
	if (!line)
		return (ftr_free(&stash, 0));
	stash = ft_extract_line(&line);
	return (line);
}

char	*read_line(int fd, char *stash, char *buffer)
{
	int		bytes_read;
	char	*temp;

	while (!ftr_strchr(stash))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ftr_free(&stash, 1));
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!stash)
			stash = ftr_strdup("");
		temp = stash;
		stash = ftr_strjoin(temp, buffer);
		free(temp);
	}
	return (stash);
}

// #include <stdlib.h>
// #include <unistd.h>

// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif

// char	*get_next_line(int fd);
// size_t	ftr_strlen(const char *s);
// char	*ftr_strchr(const char *s, int c);
// char	*ftr_strjoin(char *s1, char const *s2);
// char	*ftr_substr(char const *s, unsigned int start, size_t len);

// static char	*read_to_stash(int fd, char *stash)
// {
// 	char	*buffer;
// 	ssize_t	bytes_read;

// 	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
// 	if (!buffer)
// 		return (NULL);
// 	bytes_read = 1;
// 	while (bytes_read > 0 && !ftr_strchr(stash, '\n'))
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 		{
// 			free(buffer);
// 			free(stash);
// 			return (NULL);
// 		}
// 		if (bytes_read == 0)
// 			break ;
// 		buffer[bytes_read] = '\0';
// 		stash = ftr_strjoin(stash, buffer);
// 		if (!stash)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 	}
// 	free(buffer);
// 	return (stash);
// }

// static char	*extract_line(char *stash)
// {
// 	char	*line;
// 	size_t	line_len;
// 	char	*newline_pos;

// 	if (!stash || stash[0] == '\0')
// 		return (NULL);
// 	newline_pos = ftr_strchr(stash, '\n');
// 	if (newline_pos)
// 		line_len = (newline_pos - stash) + 1;
// 	else
// 		line_len = ftr_strlen(stash);
// 	line = ftr_substr(stash, 0, line_len);
// 	if (!line)
// 		return (NULL);
// 	return (line);
// }

// static char	*update_stash(char *stash)
// {
// 	char	*new_stash;
// 	char	*newline_pos;
// 	size_t	remaining_len;

// 	newline_pos = ftr_strchr(stash, '\n');
// 	if (!newline_pos)
// 	{
// 		free(stash);
// 		return (NULL);
// 	}
// 	remaining_len = ftr_strlen(newline_pos + 1);
// 	new_stash = ftr_substr(stash, (newline_pos - stash) + 1, remaining_len);
// 	free(stash);
// 	return (new_stash);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*stash = NULL;
// 	char		*line;

// 	stash = NULL;
// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	if (!stash)
// 	{
// 		stash = (char *)malloc(1);
// 		if (!stash)
// 			return (NULL);
// 		stash[0] = '\0';
// 	}
// 	stash = read_to_stash(fd, stash);
// 	if (!stash)
// 		return (NULL);
// 	line = extract_line(stash);
// 	if (!line)
// 	{
// 		free(stash);
// 		stash = NULL;
// 		return (NULL);
// 	}
// 	stash = update_stash(stash);
// 	if (line && line[0] == '\0')
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	return (line);
// }
