/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:46 by slangero          #+#    #+#             */
/*   Updated: 2025/04/17 01:34:36 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void getxymap(t_parse *parse, char *filename)
{
    int     fd;
    int     b;
    char    *line;

    b = 1;
    parse->sizemap.x = 1;
    parse->sizemap.y = 0;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return;
        
    b = get_next_line(fd);
    free(line);
    b = get_next_line(fd);
    
    while (line[numberblank(line)] != '1' && line[numberblank(line)] != '2'
    && line[numberblank(line)] != '0')
    {
        if (b != -1)
            free(line);
        b = get_next_line(fd);
        if (b == -1)
        {
            free(line);
            close(fd);
            return;
        }
    }
    
    getxy2(parse, b, line, fd);
    close(fd);
}

void getxy2(t_parse *parse, int b, char *line, int fd)
{
    while (b > -1 && line[0] != '\n' && line[0] != '\t' && line[0] != '\0')
    {
        if (ft_strlen(line) > parse->sizemap.x)
            parse->sizemap.x = ft_strlen(line);
        free(line);
        b = get_next_line(fd);
        b = (b == 0 ? -1 : b);
        parse->sizemap.y++;
    }
    free(line);
}

int stockmap(t_parse *parse, t_display *display)
{
    int     len;
    int     fd;

    len = 0;
    display->numberofplayer = 0;
    display->mapboleen = 1;
    if (display->textnum != 8)
        return (showerror(display, "Elements Missing"));
        
    getxymap(parse, display->filename);
    
    if (mallocmap(parse, display) != 1)
        return (0);
        
    fd = open(display->filename, O_RDONLY);
    if (fd == -1)
        return (showerror(display, "Unable to open file for map reading"));
        
    gotomap(display, parse, len, fd);
    close(fd);
    
    if (checkthewall(display) != 0)
        return (0);
        
    return (-1);
}

int gotomap(t_display *display, t_parse *parse, int len, int fd)
{
    char    *line;
    int     b;

    b = get_next_line(fd);
    while (line[numberblank(line)] != '1'
    && line[numberblank(line)] != '2' && line[numberblank(line)] != '0')
    {
        if (b != -1)
            free(line);
        b = get_next_line(fd);
        if (b == -1)
        {
            free(line);
            return (showerror(display, "Error reading map"));
        }
    }
    
    while (line[0])
    {
        sortmap(parse, line, len, display);
        if (b > -1)
            free(line);
        len++;
        b = get_next_line(fd);
        if (b == -1)
            break;
    }
    free(line);
    return (0);
}

char initposplayer(char pos, int x, int y, t_display *display)
{
    display->player_x = (double)y + 0.5;
    display->player_y = (double)x + 0.5;
    
    display->dirx = pos == 'E' ? 1 : 0;
    display->dirx = pos == 'W' ? -1 : display->dirx;
    display->diry = pos == 'S' ? 1 : 0;
    display->diry = pos == 'N' ? -1 : display->diry;
    
    display->planex = (pos == 'S') ? 0.75 : 0;
    display->planex = (pos == 'N') ? -0.75 : display->planex;
    display->planey = (pos == 'W') ? 0.75 : 0;
    display->planey = (pos == 'E') ? -0.75 : display->planey;
    
    display->numberofplayer++;
    return ('P');
}

int sortmap(t_parse *parse, char *line, int len, t_display *display)
{
    int i;

    i = 0;
    while (line[i] != '\0')
    {
        display->map[len][i] = line[i];
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            display->map[len][i] = initposplayer(line[i], i, len, display);
        i++;
    }
    
    display->map[len][i] = '\0';
    
    while (i < parse->sizemap.x)
    {
        display->map[len][i] = ' ';
        i++;
    }
    
    return (1);
}

int mallocmap(t_parse *parse, t_display *display)
{
    int i;

    if (parse->sizemap.y <= 0 || parse->sizemap.x <= 0)
        return (showerror(display, "Invalid map dimensions"));
        
    display->map = malloc(sizeof(char*) * (parse->sizemap.y + 1));
    if (!display->map)
        return (showerror(display, "Failed to allocate memory for map"));
        
    i = 0;
    while (i < parse->sizemap.y)
    {
        display->map[i] = malloc(sizeof(char) * (parse->sizemap.x + 1));
        if (!display->map[i])
        {
            while (--i >= 0)
                free(display->map[i]);
            free(display->map);
            return (showerror(display, "Failed to allocate memory for map line"));
        }
        i++;
    }
    
    display->mapx = parse->sizemap.x;
    display->mapy = parse->sizemap.y;
    display->maptofree = i;
    return (1);
}

int replacecharinmap(t_display *display, char *line, int i, int len)
{
    if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
    {
        display->map[len][i] = initposplayer(line[i], i, len, display);
        return (1);
    }
    if (line[i] == '2')
    {
        display->map[len][i] = '2';
        return (1);
    }
    return (0);
}

