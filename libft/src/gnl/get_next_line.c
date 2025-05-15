/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:40:35 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 14:23:29 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h> // For size_t, malloc, free
# include <unistd.h> // For read, ssize_t

// Define a default BUFFER_SIZE if not provided during compilation [cite: 40]
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char    *get_next_line(int fd);

// Helper function prototypes (defined in get_next_line_utils.c) [cite: 34]
size_t  ftr_strlen(const char *s);
char    *ftr_strchr(const char *s, int c);
char    *ftr_strjoin(char *s1, char const *s2);
char    *ftr_substr(char const *s, unsigned int start, size_t len);
/*
 * Reads from the file descriptor until a newline is found or EOF is reached.
 * Appends the read data to the static buffer 'stash'.
 * Returns the updated 'stash' or NULL on error.
 */
static char *read_to_stash(int fd, char *stash)
{
    char    *buffer;
    ssize_t bytes_read;

    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL); // Malloc failure

    bytes_read = 1; // Initialize to enter the loop
    while (bytes_read > 0 && !ftr_strchr(stash, '\n'))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE); // [cite: 27]
        if (bytes_read == -1) // Read error
        {
            free(buffer);
            free(stash); // Free stash on read error
            return (NULL);
        }
        if (bytes_read == 0) // EOF reached
            break;
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        stash = ftr_strjoin(stash, buffer); // Append buffer to stash
        if (!stash) // Check ft_strjoin malloc failure
        {
           free(buffer);
           return (NULL);
        }
    }
    free(buffer); // Free the temporary read buffer
    return (stash);
}

/*
 * Extracts the line (up to and including the first newline) from the stash.
 * Returns the extracted line.
 */
static char *extract_line(char *stash)
{
    char    *line;
    size_t  line_len;
    char    *newline_pos;

    if (!stash || stash[0] == '\0') // Handle empty stash
        return (NULL);

    newline_pos = ftr_strchr(stash, '\n');
    if (newline_pos)
        line_len = (newline_pos - stash) + 1; // Include the newline
    else
        line_len = ftr_strlen(stash); // No newline, take the whole stash (EOF case)

    line = ftr_substr(stash, 0, line_len);
    if (!line)
        return (NULL); // Malloc failure in ft_substr

    return (line);
}

/*
 * Updates the stash by removing the extracted line.
 * Keeps the remaining characters after the newline for the next call.
 * Returns the updated stash or NULL on malloc failure.
 */
static char *update_stash(char *stash)
{
    char    *new_stash;
    char    *newline_pos;
    size_t  remaining_len;

    newline_pos = ftr_strchr(stash, '\n');

    if (!newline_pos) // No newline found (EOF reached, stash contains last line)
    {
        free(stash); // Free the old stash [cite: 12]
        return (NULL); // Nothing left to keep
    }

    remaining_len = ftr_strlen(newline_pos + 1);
    new_stash = ftr_substr(stash, (newline_pos - stash) + 1, remaining_len);

    free(stash); // Free the old stash [cite: 12]
    return (new_stash); // Return the remaining part (or NULL if substr failed)
}

/*
 * Reads a line from a file descriptor. [cite: 27]
 * Returns the line read, including the newline character if present,
 * or NULL if there is nothing else to read or an error occurred. [cite: 30]
 */
char *get_next_line(int fd)
{
    static char *stash = NULL; // Static variable to store remainder [cite: 6]
    char        *line;

    // Input validation
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // Initialize stash if it's NULL (first call or after freeing)
    if (!stash)
    {
        stash = (char *)malloc(1); // Allocate minimal space for empty string
        if (!stash) return (NULL);
        stash[0] = '\0';
    }


    // Read from fd and append to stash until newline or EOF [cite: 44]
    stash = read_to_stash(fd, stash);
    if (!stash)
        return (NULL); // Return NULL if read_to_stash failed (read error or malloc error)

    // Extract the line from the stash
    line = extract_line(stash);
    if (!line) // Malloc error in extract_line or empty stash after read
    {
       free(stash);
       stash = NULL; // Ensure static variable is NULL for next potential call
       return (NULL);
    }


    // Update the stash for the next call
    stash = update_stash(stash);
    // Note: update_stash frees the old stash. If update_stash returns NULL (malloc error or EOF with no remainder), stash becomes NULL.

    // If line extraction resulted in an empty string (e.g., file ends exactly after a newline
    // and update_stash returned NULL), it means we are done.
    if (line && line[0] == '\0')
    {
        free(line);
        // stash is already handled by update_stash (either NULL or points to new allocation)
        return (NULL);
    }


    return (line); // Return the extracted line [cite: 29]
}


// #include "libft.h"
// #include <stdio.h>

// static void	ft_buffer_modif(char *buffer)
// {
// 	char	*b1;
// 	char	*b2;

// 	b1 = buffer;
// 	b2 = buffer;
// 	while (*b1 && *b1 != '\n')
// 		b1++;
// 	b1++;
// 	while (*b2)
// 		*b2++ = *b1++;
// 	*b2 = '\0';
// }

// static char	*ft_strverif(char *str)
// {
// 	if (!str)
// 	{
// 		printf("pas de str\n");
// 		return (ft_strdup(""));
// 	}
// 	if (str[0] == '\0')
// 	{
// 		free(str);
// 		printf("str a 0\n");
// 		return (ft_strdup(""));
// 	}
// 	else
// 		return (str);
// }

// static void	ft_bzero_mod(char *str, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		str[i] = '\0';
// 		i++;
// 	}
// }

// char	*get_next_line(int fd)
// {
// 	char		*str;
// 	static char	buffer[BUFFER_SIZE + 1];
// 	int			rd;

// 	if ((fd < 0 || fd > 1024) || BUFFER_SIZE < 0)
// 		return (NULL);
// 	rd = 1;
// 	str = NULL;
// 	while (rd > 0)
// 	{
// 		str = ft_strjoin_mod(str, buffer);
// 		if (!str)
// 			return (NULL);
// 		if (ft_findchar('\n', buffer))
// 		{
// 			ft_buffer_modif(buffer);
// 			break ;
// 		}
// 		rd = read(fd, buffer, BUFFER_SIZE);
// 		if (rd != -1)
// 			buffer[rd] = '\0';
// 		else
// 			return (ft_bzero_mod(buffer, BUFFER_SIZE + 1), free(str), NULL);
// 	}
// 	return (ft_strverif(str));
// }
