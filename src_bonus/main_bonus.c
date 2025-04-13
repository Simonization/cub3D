/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/14 01:52:16 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	draw_game(t_data *game)
{
	if (game->mlx.img.addr)
		ft_bzero(game->mlx.img.addr, HEIGHT * game->mlx.img.size_line);
	move_player(game);
	offset(&game->flag, &game->p);
	bobbing(game);
	draw_ray(game);
	if (game->flag.map != 0)
		draw_minimap(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
//nombre d'fps
	struct timeval now;
	gettimeofday(&now, NULL);
	
	float delta = (now.tv_sec - game->last_time.tv_sec)
		+ (now.tv_usec - game->last_time.tv_usec) / 1000000.0f;
	
	if (delta > 0.0f)
		game->fps = 1.0f / delta;
	
	game->last_time = now;
	
	float since_last_print = (now.tv_sec - game->last_fps_print.tv_sec)
		+ (now.tv_usec - game->last_fps_print.tv_usec) / 1000000.0f;
	
	if (since_last_print >= 0.2f)
	{
		printf("FPS: %.2f\n", game->fps);
		game->last_fps_print = now;
	}		

	return (0);
}

int	main(void)
{
	t_data	game;

	game.map = get_map();
	windows_init(&game.mlx, &game);
	player_init(&game.p);
	init_utils(&game);
	mlx_hook(game.mlx.win, 2, 1L << 0, pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, released_key, &game);
	mlx_hook(game.mlx.win, 17, 0, ft_close, &game);
	mlx_mouse_hide(game.mlx.mlx, game.mlx.win);
	mlx_hook(game.mlx.win, 6, 1L << 6, mouse, &game);
	mlx_loop_hook(game.mlx.mlx, draw_game, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
