/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodandfillmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:54 by slangero          #+#    #+#             */
/*   Updated: 2025/04/16 18:18:57 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int floodandfill(t_display *display, int mapy, int mapx)
{
    if (display->map[mapy][mapx] == '9' ||
    display->map[mapy][mapx] == 's')
    {
        if (checkaround(mapx, mapy, display) == 0)
            return (showerror(display, "Map is not surrounded/closed by walls"));
            
        if (display->map[mapy][mapx] == 's')
            display->map[mapy][mapx] = '2';
        if (display->map[mapy][mapx] == '9')
            display->map[mapy][mapx] = '0';
            
        floodandfill(display, mapy, mapx + 1);
        floodandfill(display, mapy, mapx - 1);
        floodandfill(display, mapy + 1, mapx);
        floodandfill(display, mapy - 1, mapx);
    }
    return (1);
}

int checkifgood(char c)
{
    if (c != '0' && c != '1' && c != '2' && c != 'P'
    && c != '9' && c != 's')
        return (0);
    return (1);
}

int checkifgood2(char c)
{
    if (c != '0' && c != '1' && c != '2' && c != ' '
    && c != 'N' && c != 'W' && c != 'E' && c != 'S')
        return (0);
    return (1);
}

int checkaround(int mapx, int mapy, t_display *display)
{
    if (mapy == 0 || mapy == display->mapy - 1
    || mapx == 0 || mapx == display->mapx - 1)
        return (showerror(display, "Map is not surrounded/closed by walls"));
        
    if (checkifgood(display->map[mapy + 1][mapx]) == 0)
        return (0);
    if (checkifgood(display->map[mapy - 1][mapx]) == 0)
        return (0);
    if (checkifgood(display->map[mapy][mapx + 1]) == 0)
        return (0);
    if (checkifgood(display->map[mapy][mapx - 1]) == 0)
        return (0);
        
    return (1);
}

int checkthewall(t_display *display)
{
    int mapx;
    int mapy;

    mapy = (int)display->player.x;
    mapx = (int)display->player.y;
    
    if (display->numberofplayer == 0)
        return (showerror(display, "Missing player on the map"));
    if (display->numberofplayer > 1)
        return (showerror(display, "Multiplayer mode isn't available"));
        
    floodandfill(display, mapx, mapy + 1);
    floodandfill(display, mapx, mapy - 1);
    floodandfill(display, mapx + 1, mapy);
    floodandfill(display, mapx - 1, mapy);
    
    return (0);
}

int preprocess_map(t_display *display)
{
    int x, y;
    
    y = 0;
    while (y < display->mapy)
    {
        x = 0;
        while (x < display->mapx)
        {
            if (display->map[y][x] == ' ')
            {
                if ((y > 0 && (display->map[y-1][x] == '0' || display->map[y-1][x] == 'P')) ||
                    (y < display->mapy-1 && (display->map[y+1][x] == '0' || display->map[y+1][x] == 'P')) ||
                    (x > 0 && (display->map[y][x-1] == '0' || display->map[y][x-1] == 'P')) ||
                    (x < display->mapx-1 && (display->map[y][x+1] == '0' || display->map[y][x+1] == 'P')))
                {
                    return (showerror(display, "Map not closed properly: spaces adjacent to walkable area"));
                }
            }
            
            if (display->map[y][x] == '0')
                display->map[y][x] = '9';
            else if (display->map[y][x] == '2')
                display->map[y][x] = 's';
                
            x++;
        }
        y++;
    }
    
    return (1);
}
