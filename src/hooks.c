/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:50:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 22:25:32 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_data *game)
{
	if (!game->mlx.mlx)
		ft_exit(1, NULL, &game->map);
	if (game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.no.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	if (game->mlx.so.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	if (game->mlx.we.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	if (game->mlx.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	ft_exit(0, NULL, &game->map);
	return (0);
}

int	pressed_key(int keycode, t_data *game)
{
	if (keycode == ESC)
		ft_close(game);
	else if (keycode == LEFT)
		game->p.rotate_left = true;
	else if (keycode == RIGHT)
		game->p.rotate_right = true;
	if (keycode == W)
		game->p.up = true;
	if (keycode == A)
		game->p.left = true;
	if (keycode == S)
		game->p.down = true;
	if (keycode == D)
		game->p.right = true;
	return (0);
}

int	released_key(int keycode, t_data *game)
{
	if (keycode == W)
		game->p.up = false;
	if (keycode == S)
		game->p.down = false;
	if (keycode == A)
		game->p.left = false;
	if (keycode == D)
		game->p.right = false;
	if (keycode == LEFT)
		game->p.rotate_left = false;
	if (keycode == RIGHT)
		game->p.rotate_right = false;
	return (0);
}
