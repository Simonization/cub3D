/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 00:07:30 by slangero         ###   ########.fr       */
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

t_map	convert_to_map(t_display *display, t_parse *parse)
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

t_map	parse_map(char *filename)
{
    t_display	display;
    t_parse	parse;
    

    init_parser(&display);
    display.filename = ft_strdup(filename);
    if (!display.filename)
        error_exit("Memory allocation failed");
    if (!parse(1, filename, &parse, &display))
        error_exit("Failed to parse map file");
    if (display.mapboleen == 0)
        error_exit("No valid map found in file");
    return convert_to_map(&display, &parse);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
	error_exit("Usage: ./cub3D <map_file.cub>");

	game.map = parse_map(argv[1]);
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
