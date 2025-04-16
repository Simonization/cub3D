/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:18:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 01:06:00 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int fire(int button, int x, int y, t_data *game)
{
	(void)x;
	(void)y;
	if (button == 1 && !game->weapon.is_anim)
	{
		game->weapon.is_firing = true;
		game->weapon.is_anim = true;
		game->weapon.current_img = 0;
	}
	return (0);
}

void	put_fps(t_data *game)
{
	struct timeval now;
	float delta;
	float since_last_print;

	gettimeofday(&now, NULL);
	delta = (now.tv_sec - game->last_time.tv_sec)
		+ (now.tv_usec - game->last_time.tv_usec) / 1000000.0f;
	game->delta_time = delta;
	if (delta > 0.0f)
		game->fps = 1.0f / delta;
	game->last_time = now;
	since_last_print = (now.tv_sec - game->last_fps_print.tv_sec)
		+ (now.tv_usec - game->last_fps_print.tv_usec) / 1000000.0f;
	if (since_last_print >= 0.2f)
	{
		printf("FPS: %.2f\n", game->fps);
		game->last_fps_print = now;
	}	
}

void	draw_xpm(t_data *g, t_img *img, int dst_x, int dst_y)
{
	int				x;
	int				y;
	unsigned int	color;
	char			*px;

	if (g->p.up || g->p.down || g->p.left || g->p.right)
	{
		g->weapon.bob_x = cosf(g->weapon.bob_steps) * 2.0f;
		g->weapon.bob_y = sinf(g->weapon.bob_steps) * 2.0f;
		if (!g->p.run)
			g->weapon.bob_steps += 0.15f;
		else
			g->weapon.bob_steps += 0.25f;
		if (g->weapon.bob_steps > 2.0f * PI)
			g->weapon.bob_steps -= 2.0f * PI;
	}
	else
	{
		g->flag.bobbing = 0.0f;
		g->flag.bob_steps = 0.0f;
	}
	dst_x += g->weapon.bob_x;
	dst_y += g->weapon.bob_y;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			px = img->addr + (y * img->size_line + x * (img->bpp / 8));
			color = *(unsigned int *)px;
			if ((color != 0xFF000000) != 0)
				put_pixel(&g->mlx.img, dst_x + x, dst_y + y, color);
			x++;
		}
		y++;
	}
}

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
	put_fps(game);
	if (game->weapon.is_firing)
	{
		game->weapon.anim_timer += game->delta_time;
		if (game->weapon.anim_timer >= 0.03)
		{
			game->weapon.anim_timer = 0;
			game->weapon.current_img++;
			if (game->weapon.current_img >= 7)
			{
				game->weapon.current_img = 0;
				game->weapon.is_firing = 0;
				game->weapon.is_firing = false;
				game->weapon.is_anim = false;
			}
		}
	}
	draw_xpm(game, &game->weapon.weapon[game->weapon.current_img], WIDTH / 2 - game->weapon.weapon[game->weapon.current_img].width / 2, HEIGHT - game->weapon.weapon[game->weapon.current_img].height);
	return (0);
}

void	weapon_init(t_data *game)
{
	int	i;
	char	*path;
	char	*name;
	char	*extension;
	char	*all;

	i = 0;
	path = ft_strdup("img/w");
	extension = ft_strdup(".xpm");
	game->weapon.current_img = 0;
	game->weapon.is_firing = false;
	game->weapon.is_anim = false;
	game->weapon.anim_timer = 0.0;
	while (i <= 6)
	{
		name = ft_itoa(i + 1);
		all = ft_strjoin(path, name);
		free(name);
		name = ft_strjoin(all, extension);
		free(all);
		game->weapon.weapon[i].img = mlx_xpm_file_to_image(game->mlx.mlx, name, &game->weapon.weapon[i].width, &game->weapon.weapon[i].height);
		game->weapon.weapon[i].addr = mlx_get_data_addr(game->weapon.weapon[i].img, &game->weapon.weapon[i].bpp, &game->weapon.weapon[i].size_line, &game->weapon.weapon[i].endian);
		free(name);
		i++;
	}
	free(path);
	free(extension);
}

int	main(void)
{
	t_data	game;

	game.map = get_map();
	windows_init(&game.mlx, &game);
	player_init(&game.p);
	init_utils(&game);
	weapon_init(&game);
	mlx_hook(game.mlx.win, 2, 1L << 0, pressed_key, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, released_key, &game);
	mlx_hook(game.mlx.win, 17, 0, ft_close, &game);
	mlx_mouse_hide(game.mlx.mlx, game.mlx.win);
	mlx_hook(game.mlx.win, 6, 1L << 6, mouse, &game);
	mlx_hook(game.mlx.win, 4, 1L << 2, fire, &game);
	mlx_loop_hook(game.mlx.mlx, draw_game, &game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
