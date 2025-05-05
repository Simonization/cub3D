/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:50:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/05 17:12:21 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

// ft_close avec checks po usegfault mlx

int	ft_close(t_data *game)
{
    // Check if mlx pointer itself is valid first
	if (!game || !game->mlx.mlx)
	{
        // If mlx pointer is bad, we can't do much MLX cleanup
        // Free map data if possible
        if (game && game->map.map) free_array(game->map.map);
        if (game && game->map.line_len) free(game->map.line_len);
        // Free texture paths if they were allocated
		if (game && game->map.no_path) free(game->map.no_path);
		if (game && game->map.so_path) free(game->map.so_path);
		if (game && game->map.we_path) free(game->map.we_path);
		if (game && game->map.ea_path) free(game->map.ea_path);
        exit(1); // Exit with an error code
    }

    // Now we know game->mlx.mlx is likely valid, proceed with caution
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

    // Check window pointer before destroying
	if (game->mlx.win)
	    mlx_destroy_window(game->mlx.mlx, game->mlx.win);

    // Check display pointer before destroying (might be redundant if mlx_init worked)
	// mlx_destroy_display(game->mlx.mlx); // This might not be needed if mlx_loop ends

	free(game->mlx.mlx); // Free the MLX pointer

	// Free map data
	free_array(game->map.map);
    if (game->map.line_len) // Add check for line_len
	    free(game->map.line_len);
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);

	exit(0); // Normal exit
	return (0); // Unreachable, but satisfies return type
}

// int	ft_close(t_data *game)
// {
// 	if (game->mlx.mlx && game->mlx.img.img)
// 		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
// 	if (game->mlx.mlx && game->mlx.no.img)
// 		mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
// 	if (game->mlx.mlx && game->mlx.so.img)
// 		mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
// 	if (game->mlx.mlx && game->mlx.we.img)	
// 		mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
// 	if (game->mlx.mlx && game->mlx.ea.img)
// 		mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
// 	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
// 	mlx_destroy_display(game->mlx.mlx);
// 	free(game->mlx.mlx);
// 	free_array(game->map.map);
// 	if (game->map.no_path)
// 		free(game->map.no_path);
// 	if (game->map.so_path)
// 		free(game->map.so_path);
// 	if (game->map.we_path)
// 		free(game->map.we_path);
// 	if (game->map.ea_path)
// 		free(game->map.ea_path);
// 	free(game->map.line_len);
// 	exit(0);
// 	return (0);
// }

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
