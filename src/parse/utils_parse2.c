/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:00:42 by slangero          #+#    #+#             */
/*   Updated: 2025/04/17 02:07:04 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checkcubextension(char *str, t_display *display)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (i < 5) // Need at least ".cub"
        return (showerror(display, "Invalid filename"));
    
    if (str[i - 1] == 'b' && str[i - 2] == 'u'
    && str[i - 3] == 'c' && str[i - 4] == '.')
    {
        if ((i = open(str, O_RDONLY)) == -1)
            return (showerror(display, "File Name is not correct"));
        close(i);
        return (1);
    }
    return (showerror(display, "Files without .cub extension are not accepted"));
}

int	strlentoend(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\0')
        i++;
    return (i);
}

int	isend(char *line)
{
    if (*line == '\n' || *line == '\0' || *line == ' ')
        return (1);
    return (0);
}

int	numberblank(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    return (i);
}

int	searchcomma(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        return (i);
    return (-1);
}