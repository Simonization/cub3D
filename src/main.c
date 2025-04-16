/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 01:07:24 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_game(t_data *game)
{
	if (game->mlx.img.addr)
		ft_bzero(game->mlx.img.addr, HEIGHT * game->mlx.img.size_line);
	move_player(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
	return (0);
}

void	error_exit(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
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

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
	error_exit("Usage: ./cub3D <map_file.cub>");

	game.map = load_map(argv[1]);
	windows_init(&game.mlx, &game);
	player_init(&game.player);
	init_trigo(&game);
	mlx_hook(game.mlx.win, 2, 1L << 0, pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, released_key, &game);
	mlx_hook(game.mlx.win, 17, 0, ft_close, &game);
	mlx_loop_hook(game.mlx.mlx, draw_game, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
