/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 21:40:13 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	draw_game(t_data *game)
{
	if (game->mlx.img.addr)
		ft_bzero(game->mlx.img.addr, game->img_size);
	move_player(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
	return (0);
}

void	print_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int	validate_map_file(char *file_path)
{
	int	len;
	int	fd;

	len = ft_strlen(file_path);
	if (len < 5 || ft_strncmp(file_path + len - 4, ".cub", 4) != 0)
		return (print_error("File must have .cub extension"), 0);
	if (access(file_path, F_OK) == -1)
		return (print_error("File does not exist"), 0);
	if (access(file_path, R_OK) == -1)
		return (print_error("Permission denied: cannot read file"), 0);
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (print_error("Failed to open file"), 0);
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"), 1);
	if (!validate_map_file(argv[1]))
		return (1);
	game.map = parse_map(argv[1]);
	if (!game.map.map || !game.map.no_path || !game.map.so_path
		|| !game.map.we_path || !game.map.ea_path
		|| game.map.floor_color == 0 || game.map.ceiling_color == 0)
		return (1);
	if (!validate_map(&game.map))
		ft_exit(1, NULL, &game.map);
	windows_init(&game.mlx, &game);
	player_init(&game.p, get_player_pos(game.map));
	init_utils(&game);
	mlx_hook(game.mlx.win, 2, 1L << 0, pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, released_key, &game);
	mlx_hook(game.mlx.win, 17, 0, ft_close, &game);
	mlx_loop_hook(game.mlx.mlx, draw_game, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
