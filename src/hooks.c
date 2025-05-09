/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:50:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/09 17:37:48 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

int	ft_close(t_data *game)
{
	if (!game || !game->mlx.mlx)
	{
        if (game && game->map.map) free_array(game->map.map);
        if (game && game->map.line_len) free(game->map.line_len);
		if (game && game->map.no_path) free(game->map.no_path);
		if (game && game->map.so_path) free(game->map.so_path);
		if (game && game->map.we_path) free(game->map.we_path);
		if (game && game->map.ea_path) free(game->map.ea_path);
        exit(1);
    }
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
	free(game->mlx.mlx);
	free_array(game->map.map);
    if (game->map.line_len)
	    free(game->map.line_len);
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);

	exit(0);
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
