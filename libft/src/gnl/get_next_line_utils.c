/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:54:08 by qalpesse          #+#    #+#             */
/*   Updated: 2025/05/15 14:23:50 by agoldber         ###   ########.fr       */
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
 * Calculates the length of a string.
 * Excludes the terminating null byte ('\0').
 */
size_t ftr_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}

/*
 * Locates the first occurrence of character 'c' (converted to a char)
 * in the string pointed to by 's'.
 * Returns a pointer to the located character, or NULL if not found.
 */
char *ftr_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0') // Check for null terminator as well
        return ((char *)s);
    return (NULL);
}

/*
 * Allocates (with malloc(3)) and returns a new string,
 * which is the result of the concatenation of 's1' and 's2'.
 * Frees the original 's1' after joining.
 */
char *ftr_strjoin(char *s1, char const *s2)
{
    char    *new_str;
    size_t  s1_len;
    size_t  s2_len;
    size_t  i;
    size_t  j;

    if (!s2)
        return (s1); // Return original s1 if s2 is NULL
    s1_len = ftr_strlen(s1);
    s2_len = ftr_strlen(s2);
    new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!new_str)
    {
        free(s1); // Free s1 on malloc failure
        return (NULL);
    }
    i = -1;
    while (++i < s1_len)
        new_str[i] = s1[i];
    j = -1;
    while (++j < s2_len)
        new_str[i + j] = s2[j];
    new_str[i + j] = '\0';
    free(s1); // Free the old s1 [cite: 12]
    return (new_str);
}


/*
 * Allocates (with malloc(3)) and returns a substring from the string 's'.
 * The substring begins at index 'start' and is of maximum size 'len'.
 */
char *ftr_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ftr_strlen(s);
	if (start >= s_len) // If start index is out of bounds, return empty string
		len = 0;
	else if (len > s_len - start) // Adjust len if it exceeds remaining string length
		len = s_len - start;

	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);

	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}


// #include "libft.h"

// static int	ft_strlen_bn(char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i] && str[i] != '\n')
// 		i++;
// 	if (str[i] == '\n')
// 		i++;
// 	return (i);
// }

// static char	*ft_freestr(char *str)
// {
// 	if (str != NULL)
// 		free(str);
// 	return (NULL);
// }

// char	*ft_strjoin_mod(char *s1, char *s2)
// {
// 	char	*ptr;
// 	char	*tmp;
// 	char	*sub_s1;

// 	sub_s1 = s1;
// 	ptr = malloc(ft_strlen_bn(s1) + ft_strlen_bn(s2) + 1);
// 	if (!ptr)
// 		return (ft_freestr(s1));
// 	tmp = ptr;
// 	if (s1)
// 	{
// 		while (*s1 && *s1 != '\n')
// 			*tmp++ = *s1++;
// 	}
// 	while (*s2 && *s2 != '\n')
// 		*tmp++ = *s2++;
// 	*tmp = '\0';
// 	ft_freestr(sub_s1);
// 	return (ptr);
// }

// int	ft_findchar(char c, char *str)
// {
// 	if (!str)
// 		return (0);
// 	while (*str)
// 	{
// 		if (*str == c)
// 			return (1);
// 		str++;
// 	}
// 	return (0);
// }
