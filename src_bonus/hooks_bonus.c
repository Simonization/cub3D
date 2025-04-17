/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:50:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 20:29:29 by agoldber         ###   ########.fr       */
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

void	pressed_key2(int keycode, t_data *game)
{
	if (keycode == P)
	{
		game->flag.map++;
		if (game->flag.map > 2)
			game->flag.map = 0;
	}
	else if (keycode == SPACE && !game->flag.jump
		&& game->flag.jump_offset == 0.0f && !game->flag.crouch)
	{
		game->flag.jump = true;
		game->flag.jump_time = 0.0f;
	}
	else if (keycode == CROUCH && !game->flag.jump)
	{
		game->flag.crouch = !game->flag.crouch;
	}
}

int	pressed_key(int keycode, t_data *game)
{
	if (keycode == ESC)
		ft_close(game);
	else if (keycode == A)
		game->p.left = true;
	else if (keycode == W)
		game->p.up = true;
	else if (keycode == S)
		game->p.down = true;
	else if (keycode == D)
		game->p.right = true;
	else if (keycode == LEFT)
		game->p.rotate_left = true;
	else if (keycode == RIGHT)
		game->p.rotate_right = true;
	else if (keycode == SHIFT)
		game->p.run = true;
	else if (keycode == UP)
		game->flag.head_up = true;
	else if (keycode == DOWN)
		game->flag.head_down = true;
	pressed_key2(keycode, game);
	return (0);
}

int	released_key(int keycode, t_data *game)
{
	if (keycode == A)
		game->p.left = false;
	else if (keycode == W)
		game->p.up = false;
	else if (keycode == S)
		game->p.down = false;
	else if (keycode == D)
		game->p.right = false;
	else if (keycode == LEFT)
		game->p.rotate_left = false;
	else if (keycode == RIGHT)
		game->p.rotate_right = false;
	else if (keycode == SHIFT)
		game->p.run = false;
	else if (keycode == UP)
		game->flag.head_up = false;
	else if (keycode == DOWN)
		game->flag.head_down = false;
	return (0);
}

int	mouse(int x, int y, t_data *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = x - X_CENTER;
	if (delta_x != 0)
	{
		game->p.angle -= delta_x * 0.002f;
		mlx_mouse_move(game->mlx.mlx, game->mlx.win, X_CENTER, Y_CENTER);
	}
	delta_y = y - Y_CENTER;
	if (delta_y != 0)
	{
		game->flag.head_offset -= delta_y;
		mlx_mouse_move(game->mlx.mlx, game->mlx.win, X_CENTER, Y_CENTER);
	}
	return (0);
}
