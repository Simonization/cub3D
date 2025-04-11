/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/11 20:37:30 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	head_offset(t_flag *f, t_player *player)
{
	if (f->head_up && !player->run)
		f->head_offset += 10;
	if (f->head_up && player->run)
		f->head_offset += 15;
	if (f->head_down && !player->run)
		f->head_offset -= 10;
	if (f->head_down && player->run)
		f->head_offset -= 15;
	if (f->head_offset > 360)
		f->head_offset = 360;
	if (f->head_offset < -360)
		f->head_offset = -360;
}

int	draw_game(t_data *game)
{
	/*pour la minimap, ajouter :
	draw_direction(&game->player, &game->mlx.img, game->map.map);*/
	if (game->mlx.img.addr)
		ft_bzero(game->mlx.img.addr, HEIGHT * game->mlx.img.size_line);
	move_player(&game->player, game->map);
	head_offset(&game->flag, &game->player);
	draw_ray(game);
	draw_map(game->map.map, &game->mlx.img);
	draw_player(game->player.co, &game->mlx.img);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win,
		game->mlx.img.img, 0, 0);
	return (0);
}

int	mouse(int x, int y, t_data *game)
{
	int	delta_x;
	int	delta_y;

	delta_x = x - X_CENTER;
	if (delta_x != 0)
	{
		game->player.angle -= delta_x * 0.002f;
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

int	main(void)
{
	t_data	game;

	game.map = get_map();
	windows_init(&game.mlx, &game);
	player_init(&game.player);
	init_flag(&game.flag);
	mlx_hook(game.mlx.win, 2, 1L << 0, pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, released_key, &game);
	mlx_hook(game.mlx.win, 17, 0, ft_close, &game);
	mlx_mouse_hide(game.mlx.mlx, game.mlx.win);
	mlx_hook(game.mlx.win, 6, 1L << 6, mouse, &game);
	mlx_loop_hook(game.mlx.mlx, draw_game, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
