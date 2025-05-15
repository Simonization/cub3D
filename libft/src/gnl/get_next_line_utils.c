/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 18:58:58 by slangero          #+#    #+#             */
/*   Updated: 2025/05/12 19:23:36 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// char	*ftr_strchr(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (!s)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (s[i] == '\n')
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if (s[i] == '\n')
// 		return ((char *)&s[i]);
// 	return (NULL);
// }

// int	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strdup(char *s)
// {
// 	char				*dupstr;
// 	unsigned int		i;

// 	if (!s)
// 		return (NULL);
// 	dupstr = malloc(sizeof(char) * (ft_strlen(s) + 1));
// 	if (!dupstr)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		dupstr[i] = s[i];
// 		i++;
// 	}
// 	dupstr[i] = '\0';
// 	return (dupstr);
// }

// char	*ft_substr(char *s, int start, int len)
// {
// 	char	*substr;
// 	int		i;

// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (malloc(1));
// 	if (len > ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	substr = malloc(sizeof(char) * (len + 1));
// 	if (!substr)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		substr[i] = s[start + i];
// 		i++;
// 	}
// 	substr[i] = 0;
// 	return (substr);
// }

// char	*ft_strjoin(char *str, char *buff)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	i = 0;
// 	j = 0;
// 	res = (char *)malloc((ft_strlen(str) + ft_strlen(buff) + 1) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	while (str && str[j])
// 		res[i++] = str[j++];
// 	j = 0;
// 	while (buff[j])
// 		res[i++] = buff[j++];
// 	res[i] = '\0';
// 	return (res);
// }

// // #include <stdlib.h>
// // #include <unistd.h>

// // #ifndef BUFFER_SIZE
// // # define BUFFER_SIZE 42
// // #endif

// // char	*get_next_line(int fd);
// // size_t	ftr_strlen(const char *s);
// // char	*ftr_strchr(const char *s, int c);
// // char	*ftr_strjoin(char *s1, char const *s2);
// // char	*ftr_substr(char const *s, unsigned int start, size_t len);

// // size_t	ftr_strlen(const char *s)
// // {
// // 	size_t	i;

// // 	i = 0;
// // 	if (!s)
// // 		return (0);
// // 	while (s[i])
// // 		i++;
// // 	return (i);
// // }

// // char	*ftr_strchr(const char *s, int c)
// // {
// // 	if (!s)
// // 		return (NULL);
// // 	while (*s)
// // 	{
// // 		if (*s == (char)c)
// // 			return ((char *)s);
// // 		s++;
// // 	}
// // 	if ((char)c == '\0')
// // 		return ((char *)s);
// // 	return (NULL);
// // }

// // char	*ftr_strjoin(char *s1, char const *s2)
// // {
// // 	char	*new_str;
// // 	size_t	s1_len;
// // 	size_t	s2_len;
// // 	size_t	i;
// // 	size_t	j;

// // 	if (!s2)
// // 		return (s1);
// // 	s1_len = ftr_strlen(s1);
// // 	s2_len = ftr_strlen(s2);
// // 	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
// // 	if (!new_str)
// // 	{
// // 		free(s1);
// // 		return (NULL);
// // 	}
// // 	i = -1;
// // 	while (++i < s1_len)
// // 		new_str[i] = s1[i];
// // 	j = -1;
// // 	while (++j < s2_len)
// // 		new_str[i + j] = s2[j];
// // 	new_str[i + j] = '\0';
// // 	free(s1);
// // 	return (new_str);
// // }

// // char	*ftr_substr(char const *s, unsigned int start, size_t len)
// // {
// // 	char	*sub;
// // 	size_t	s_len;
// // 	size_t	i;

// // 	if (!s)
// // 		return (NULL);
// // 	s_len = ftr_strlen(s);
// // 	if (start >= s_len)
// // 		len = 0;
// // 	else if (len > s_len - start)
// // 		len = s_len - start;
// // 	sub = (char *)malloc(sizeof(char) * (len + 1));
// // 	if (!sub)
// // 		return (NULL);
// // 	i = 0;
// // 	while (i < len)
// // 	{
// // 		sub[i] = s[start + i];
// // 		i++;
// // 	}
// // 	sub[i] = '\0';
// // 	return (sub);
// // }
