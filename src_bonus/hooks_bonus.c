/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:50:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/11 18:08:45 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_close(t_data *game)
{
	if (game->mlx.mlx && game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.mlx && game->mlx.no.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	if (game->mlx.mlx && game->mlx.so.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	if (game->mlx.mlx && game->mlx.we.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	if (game->mlx.mlx && game->mlx.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	free_array(game->map.map);
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	free(game->map.line_len);
	exit(0);
	return (0);
}

int	pressed_key(int keycode, t_data *game)
{
	if (keycode == ESC)
		ft_close(game);
	else if (keycode == A)
		game->player.left = true;
	else if (keycode == W)
		game->player.up = true;
	else if (keycode == S)
		game->player.down = true;
	else if (keycode == D)
		game->player.right = true;
	else if (keycode == LEFT)
		game->player.rotate_left = true;
	else if (keycode == RIGHT)
		game->player.rotate_right = true;
	else if (keycode == SHIFT)
		game->player.run = true;
	else if (keycode == UP)
		game->flag.head_up = true;
	else if (keycode == DOWN)
		game->flag.head_down = true;
	return (0);
}

int	released_key(int keycode, t_data *game)
{
	if (keycode == A)
		game->player.left = false;
	else if (keycode == W)
		game->player.up = false;
	else if (keycode == S)
		game->player.down = false;
	else if (keycode == D)
		game->player.right = false;
	else if (keycode == LEFT)
		game->player.rotate_left = false;
	else if (keycode == RIGHT)
		game->player.rotate_right = false;
	else if (keycode == SHIFT)
		game->player.run = false;
	else if (keycode == UP)
		game->flag.head_up = false;
	else if (keycode == DOWN)
		game->flag.head_down = false;
	return (0);
}
