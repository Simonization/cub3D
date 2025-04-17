/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:12:31 by slangero          #+#    #+#             */
/*   Updated: 2025/04/17 02:15:24 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

t_map load_map(char *filename)
{
    t_display display;
    t_parse parse;
    t_map map;
    int i;
    
    init_parser(&display);
    if (!parse_map(1, filename, &parse, &display))
    {
        printf("Error: Failed to parse the map file\n");
        return get_sample_map();
    }
    if (stockmap(&parse, &display) <= 0)
    {
        printf("Error: Invalid map format\n");
        return get_sample_map();
    }
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
    if (display.north) free(display.north);
    if (display.south) free(display.south);
    if (display.west) free(display.west);
    if (display.east) free(display.east);
    if (display.spritepwd) free(display.spritepwd);
    if (display.filename) free(display.filename);
    
    return map;
}

t_map	convert_to_map(t_display *display)
{
	t_map	map;
	int	i;

	map.map = display->map;
	map.line_len = malloc(sizeof(int) * display->mapy);
	if (!map.line_len)
		error_exit("Memory allocation failed");
	i = 0;
	while (i < display->mapy)
	{
		map.line_len[i] = ft_strlen(display->map[i]);
		i++;
	}
	map.floor_color = (display->rgbfloor[0] << 16) | 
					  (display->rgbfloor[1] << 8) | 
					  display->rgbfloor[2];
	
	map.ceiling_color = (display->rgbceiling[0] << 16) | 
						(display->rgbceiling[1] << 8) | 
						display->rgbceiling[2];
	map.no_path = ft_strdup(display->north);
	map.so_path = ft_strdup(display->south);
	map.we_path = ft_strdup(display->west);
	map.ea_path = ft_strdup(display->east);
	if (!map.no_path || !map.so_path || !map.we_path || !map.ea_path)
		error_exit("Memory allocation failed for texture paths");
	return map;
}

int	checkparse(t_display *display, t_parse *parse, int fd)
{
	char	*line;
	int		continue_parsing;

	continue_parsing = 1;
	while (continue_parsing)
	{
		line = get_next_line(fd);
		if (!line)
		{
			continue_parsing = 0;
			continue;
		}
		
		if (line[numberblank(line)] == '1' || line[0] == '\0')
			continue_parsing = 0;
			
		if (parseline(line, parse, display) == -1)
			continue_parsing = 0;
			
		free(line);
	}
	
	close(fd);
	
	if (display->textnum < 8)
		return (showerror(display, "Elements Missing"));
	if (display->textnum > 8)
		return (showerror(display, "Duplicate Element"));
	if (display->mapboleen == 0)
		return (showerror(display, "Missing Map"));
		
	return (0);
}

int	parseline(char *line, t_parse *parse, t_display *display)
{
    int index;

    index = 0 + numberblank(line);
    if (line[index] == '\0' || line[index] == '\n')
        return (1);
    
    if (line[index] == 'R')
        return (stockresolution(line + index + 1, parse, display));
    if (line[index] == 'N' && line[index + 1] == 'O')
        return (stocktextures_no(line + index + 2, display));
    if (line[index] == 'S' && line[index + 1] == 'O')
        return (stocktextures_so(line + index + 2, display));
    if (line[index] == 'W' && line[index + 1] == 'E')
        return (stocktextures_we(line + index + 2, display));
    if (line[index] == 'E' && line[index + 1] == 'A')
        return (stocktextures_ea(line + index + 2, display));
    if (line[index] == 'S' && line[index + 1] == ' ')
        return (stocktextures_s(line + index + 1, display));
    if (line[index] == 'F' && line[index + 1] == ' ')
        return (stockcolorf(line + index + 1, display));
    if (line[index] == 'C' && line[index + 1] == ' ')
        return (stockcolorc(line + index + 1, display));
    if (line[index] == '1' || line[index] == '2' || line[index] == '0')
        return (stockmap(parse, display));
    
    return (showerror(display, "One or more elements in .cub are not correct"));
}