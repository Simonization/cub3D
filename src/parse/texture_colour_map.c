/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_colour_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:19:09 by slangero          #+#    #+#             */
/*   Updated: 2025/04/17 01:30:11 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int stockcolorf(char *line, t_display *display)
{
    int i;
    int r, g, b;
    char *temp;

    i = numberblank(line);
    
    r = ft_atoi(line + i);
    if (r < 0 || r > 255)
        return (showerror(display, "Color of Floor must be between 0 and 255 (RGB)"));
    
    i += numberblank(line + i);
    if (searchcomma(line + i) == -1)
        return (showerror(display, "Missing first comma in Floor color"));
    i += searchcomma(line + i) + 1;
    
    g = ft_atoi(line + i);
    if (g < 0 || g > 255)
        return (showerror(display, "Color of Floor must be between 0 and 255 (RGB)"));
    
    i += numberblank(line + i);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    i += numberblank(line + i);
    if (line[i] != ',')
        return (showerror(display, "Missing second comma in Floor color"));
    i++;
    
    b = ft_atoi(line + i);
    if (b < 0 || b > 255)
        return (showerror(display, "Color of Floor must be between 0 and 255 (RGB)"));
    
    display->rgbfloor[0] = r;
    display->rgbfloor[1] = g;
    display->rgbfloor[2] = b;
    
    display->textnum++;
    return (1);
}

int stockcolorc(char *line, t_display *display)
{
    int i;
    int r, g, b;

    i = numberblank(line);
    
    r = ft_atoi(line + i);
    if (r < 0 || r > 255)
        return (showerror(display, "Color of Ceiling must be between 0 and 255 (RGB)"));
    
    i += numberblank(line + i);
    if (searchcomma(line + i) == -1)
        return (showerror(display, "Missing first comma in Ceiling color"));
    i += searchcomma(line + i) + 1;
    
    g = ft_atoi(line + i);
    if (g < 0 || g > 255)
        return (showerror(display, "Color of Ceiling must be between 0 and 255 (RGB)"));
    
    i += numberblank(line + i);
    while (line[i] >= '0' && line[i] <= '9')
        i++;
    i += numberblank(line + i);
    if (line[i] != ',')
        return (showerror(display, "Missing second comma in Ceiling color"));
    i++;
    
    b = ft_atoi(line + i);
    if (b < 0 || b > 255)
        return (showerror(display, "Color of Ceiling must be between 0 and 255 (RGB)"));
    
    display->rgbceiling[0] = r;
    display->rgbceiling[1] = g;
    display->rgbceiling[2] = b;
    
    display->textnum++;
    return (1);
}

int stockresolution(char *line, t_parse *parse, t_display *display)
{
    int v;
    int i;

    v = 0;
    i = numberblank(line);
    if (i < 1)
        return (showerror(display, "Wrong argument syntax for Resolution"));
        
    parse->r1 = ft_atoi(line + i);
    if (parse->r1 <= 0)
        return (showerror(display, "Invalid first argument for Resolution"));
        
    while (line[i + v] && (line[i + v] != ' '))
        v++;
    if (v < 1)
        return (showerror(display, "Wrong argument syntax for Resolution"));
    i += v;
    
    parse->r2 = ft_atoi(line + i);
    if (parse->r2 <= 0)
        return (showerror(display, "Invalid second argument for Resolution"));
        
    display->textnum++;
    return (1);
}

int stocktextures_no(char *line, t_display *display)
{
    int i;
    int l;

    i = numberblank(line);
    l = 0;
    
    if (display->north != NULL)
        return (showerror(display, "Texture NO is duplicated"));
        
    if (((display->north = malloc(sizeof(char) * strlentoend(line + i) + 1))) == NULL)
        return (showerror(display, "Unable to Malloc"));
        
    if ((open(line + i, O_RDONLY) == -1))
        return (showerror(display, "Texture NO not existing"));
        
    while (isend(line + i + l) == 0 && line[i + l])
    {
        display->north[l] = line[i + l];
        l++;
    }
    display->north[l] = '\0';
    
    display->textnum++;
    return (1);
}

int stocktextures_so(char *line, t_display *display)
{
    int i;
    int l;

    i = numberblank(line);
    l = 0;
    
    if (display->south != NULL)
        return (showerror(display, "Texture SO is duplicated"));
        
    if ((open(line + i, O_RDONLY) == -1))
        return (showerror(display, "Texture SO not existing"));
        
    if (((display->south = malloc(sizeof(char) * strlentoend(line + i) + 1))) == 0)
        return (showerror(display, "Unable to Malloc"));
        
    while (isend(line + i + l) == 0 && line[i + l])
    {
        display->south[l] = line[i + l];
        l++;
    }
    display->south[l] = '\0';
    
    display->textnum++;
    return (1);
}

int stocktextures_we(char *line, t_display *display)
{
    int i;
    int l;

    i = numberblank(line);
    l = 0;
    
    if (display->west != NULL)
        return (showerror(display, "Texture WE is duplicated"));
        
    if ((open(line + i, O_RDONLY) == -1))
        return (showerror(display, "Texture WE not existing"));
        
    if (((display->west = malloc(sizeof(char) * strlentoend(line + i) + 1))) == 0)
        return (showerror(display, "Unable to Malloc"));
        
    while (isend(line + i + l) == 0 && line[i + l])
    {
        display->west[l] = line[i + l];
        l++;
    }
    display->west[l] = '\0';
    
    display->textnum++;
    return (1);
}

int stocktextures_ea(char *line, t_display *display)
{
    int i;
    int l;

    i = numberblank(line);
    l = 0;
    
    if (display->east != NULL)
        return (showerror(display, "Texture EA is duplicated"));
        
    if ((open(line + i, O_RDONLY) == -1))
        return (showerror(display, "Texture EA not existing"));
        
    if (((display->east = malloc(sizeof(char) * strlentoend(line + i) + 1))) == 0)
        return (showerror(display, "Unable to Malloc"));
        
    while (isend(line + i + l) == 0 && line[i + l])
    {
        display->east[l] = line[i + l];
        l++;
    }
    display->east[l] = '\0';
    
    display->textnum++;
    return (1);
}

int stocktextures_s(char *line, t_display *display)
{
    int i;
    int l;

    i = numberblank(line);
    l = 0;
    
    if (display->spritepwd != NULL)
        return (showerror(display, "Texture S is duplicated"));
        
    if ((open(line + i, O_RDONLY) == -1))
        return (showerror(display, "Texture Sprite not existing"));
        
    if (((display->spritepwd = malloc(sizeof(char) * strlentoend(line + i) + 1))) == 0)
        return (showerror(display, "Unable to Malloc"));
        
    while (isend(line + i + l) == 0 && line[i + l])
    {
        display->spritepwd[l] = line[i + l];
        l++;
    }
    display->spritepwd[l] = '\0';
    
    display->textnum++;
    return (1);
}

unsigned int colortoint(unsigned int r, unsigned int g, unsigned int b)
{
    return (r << 16 | g << 8 | b);
}
