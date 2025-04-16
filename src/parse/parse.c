/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:34 by slangero          #+#    #+#             */
/*   Updated: 2025/04/16 18:18:38 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int init_parser(t_display *display)
{
    display->mapboleen = 0;
    display->initsuccess = 0;
    display->textnum = 0;
    display->errorbool = 0;
    display->maptofree = -1;
    display->south = NULL;
    display->north = NULL;
    display->west = NULL;
    display->east = NULL;
    display->spritepwd = NULL;
    display->filename = NULL;
    return (0);
}

int parse(int argc, char *str, t_parse *parse, t_display *display)
{
    int     fd;

    if (argc == 3)
        display->bmp = 1;
    else
        display->bmp = 0;
        
    if (display->filename == NULL)
    {
        display->filename = malloc(sizeof(char) * strlentoend(str) + 1);
        if (!display->filename)
            return (showerror(display, "Unable to Malloc"));
    }
    
    if (checkcubextension(str, display) != 1)
        return (0);  // Error is handled in checkcubextension
        
    ft_strcpy(display->filename, str);
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (showerror(display, "Unable to open file"));
        
    display->fd = fd;
    if (checkparse(display, parse, fd) != 0)
        return (0);  // Error is handled in checkparse
        
    return (1);
}

// Moved player initialization from init_player to a helper function
void init_player_position(t_data *game, t_display *display)
{
    game->player.co.x = display->player_x * BLOCK_SIZE;
    game->player.co.y = display->player_y * BLOCK_SIZE;
    
    // Calculate the initial angle based on direction
    if (display->dirx == 1) // East
        game->player.angle = 0;
    else if (display->dirx == -1) // West
        game->player.angle = PI;
    else if (display->diry == 1) // South
        game->player.angle = PI / 2;
    else if (display->diry == -1) // North
        game->player.angle = 3 * PI / 2;
    
    // Other player properties remain the same
    game->player.co.color = 0x0000FF00;
    game->player.up = false;
    game->player.down = false;
    game->player.right = false;
    game->player.left = false;
    game->player.rotate_left = false;
    game->player.rotate_right = false;
}

// A simple sample map for testing - to be removed once parsing is working
t_map get_sample_map(void)
{
    t_map map;
    int i = -1;
    
    map.ceiling_color = 0x00451CCB;
    map.floor_color = 0x00361997;
    map.no_path = ft_strdup("img/among-us-yellow-shakes-booty.xpm");
    map.so_path = ft_strdup("img/among-us-red-shakes-booty.xpm");
    map.we_path = ft_strdup("img/among-us-purple-shakes-booty.xpm");
    map.ea_path = ft_strdup("img/among-us-green-shakes-booty.xpm");
    
    map.map = malloc(sizeof(char *) * 11);
    map.map[0] = ft_strdup("111111111111111111");
    map.map[1] = ft_strdup("100000000000000001");
    map.map[2] = ft_strdup("100000000000000001");
    map.map[3] = ft_strdup("100000N00000000001");
    map.map[4] = ft_strdup("100000000000000001");
    map.map[5] = ft_strdup("100000000000000001");
    map.map[6] = ft_strdup("100000000000000001");
    map.map[7] = ft_strdup("100000000000000001");
    map.map[8] = ft_strdup("100000000000000001");
    map.map[9] = ft_strdup("111111111111111111");
    map.map[10] = NULL;
    
    map.line_len = malloc(sizeof(int) * 11);
    while (map.map[++i])
        map.line_len[i] = ft_strlen(map.map[i]);
        
    return map;
}

// New function to load a map file
t_map load_map(char *filename)
{
    t_display display;
    t_parse parse;
    t_map map;
    int i;
    
    // Initialize the display structure
    init_parser(&display);
    
    // Parse the map file
    if (!parse(1, filename, &parse, &display))
    {
        printf("Error: Failed to parse the map file\n");
        // Return a sample map if parsing fails (for testing)
        return get_sample_map();
    }
    
    // Process the map after parsing
    if (stockmap(&parse, &display) <= 0)
    {
        printf("Error: Invalid map format\n");
        return get_sample_map();
    }
    
    // Convert the parsed data to t_map structure
    map.map = display.map;
    map.line_len = malloc(sizeof(int) * display.mapy);
    if (!map.line_len)
    {
        printf("Error: Memory allocation failed\n");
        return get_sample_map();
    }
    
    i = 0;
    while (i < display.mapy)
    {
        map.line_len[i] = ft_strlen(display.map[i]);
        i++;
    }
    
    // Set colors and texture paths
    map.ceiling_color = (display.rgbceiling[0] << 16) | 
                        (display.rgbceiling[1] << 8) | 
                        display.rgbceiling[2];
                        
    map.floor_color = (display.rgbfloor[0] << 16) | 
                      (display.rgbfloor[1] << 8) | 
                      display.rgbfloor[2];
                      
    map.no_path = display.north ? ft_strdup(display.north) : ft_strdup("img/default_north.xpm");
    map.so_path = display.south ? ft_strdup(display.south) : ft_strdup("img/default_south.xpm");
    map.we_path = display.west ? ft_strdup(display.west) : ft_strdup("img/default_west.xpm");
    map.ea_path = display.east ? ft_strdup(display.east) : ft_strdup("img/default_east.xpm");
    
    // Free the display structure resources
    if (display.north) free(display.north);
    if (display.south) free(display.south);
    if (display.west) free(display.west);
    if (display.east) free(display.east);
    if (display.spritepwd) free(display.spritepwd);
    if (display.filename) free(display.filename);
    
    return map;
}