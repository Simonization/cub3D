/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/29 16:33:54 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

static int validate_file(char *path)
{
	int len;
	int fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	
	return (1);
}

static int print_error(char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int main(int argc, char **argv)
{
	t_data game;
	char *file_path;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"));
	
	file_path = argv[1];
	
	if (!validate_file(file_path))
		return (print_error("Invalid map file"));
	
	if (!parse_map(file_path, &game.map))
		return (1); 
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
