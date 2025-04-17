/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:09:40 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 14:55:01 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_data *game)
{
	t_trigo	perp;

	perp.cos_a = game->trigo.cos_l;
	perp.sin_a = game->trigo.sin_l;
	draw_triangle_side(game->trigo, perp, &game->mlx.img);
	perp.cos_a = game->trigo.cos_r;
	perp.sin_a = game->trigo.sin_r;
	draw_triangle_side(game->trigo, perp, &game->mlx.img);
}

int	check_limit(t_data *game, t_coord co, t_coord limit)
{
	if (game->flag.map == 1)
	{
		if (co.y >= limit.x && co.y < limit.y
			&& co.x >= limit.x && co.x < limit.y)
			return (1);
	}
	else
	{
		if ((co.x - MINIMAP_CENTER + 5) * (co.x - MINIMAP_CENTER + 5)
			+ (co.y - MINIMAP_CENTER + 5) * (co.y - MINIMAP_CENTER + 5)
			<= (MINIMAP_RADIUS - 12) * (MINIMAP_RADIUS - 12))
			return (1);
	}
	return (0);
}

void	draw_map(char **map, t_data *game, t_coord limit)
{
	t_coord	co;
	t_coord	co2;

	co.y = 0;
	co2.color = 0x00AAAADD;
	while (map[co.y])
	{
		co.x = 0;
		co2.y = ((co.y - (game->p.co.y / BLOCK_SIZE))
				* TILES_SIZE) + MINIMAP_CENTER;
		while (map[co.y][co.x])
		{
			co2.x = ((co.x - (game->p.co.x / BLOCK_SIZE))
					* TILES_SIZE) + MINIMAP_CENTER;
			if (check_limit(game, co2, limit) && map[co.y][co.x] == '1')
				draw_square(co2, TILES_SIZE, true, &game->mlx.img);
			co.x++;
		}
		co.y++;
	}
}

void	draw_circle(t_img *img, int c, int r, int color)
{
	int	x;
	int	y;

	y = c - r;
	while (y <= c + r)
	{
		x = c - r;
		while (x <= c + r)
		{
			if ((x - c) * (x - c) + (y - c) * (y - c) <= r * r)
				put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *game)
{
	t_coord	co;

	co.x = 10;
	co.y = 10;
	co.color = 0x00000000;
	if (game->flag.map == 1)
		draw_square(co, MINIMAP_SIZE, true, &game->mlx.img);
	else
		draw_circle(&game->mlx.img, MINIMAP_CENTER + 5,
			MINIMAP_RADIUS + 5, co.color);
	co.x += 10;
	co.y += 10;
	co.color = 0x00FFFFFF;
	if (game->flag.map == 1)
		draw_square(co, MINIMAP_SIZE - 20, true, &game->mlx.img);
	else
		draw_circle(&game->mlx.img, MINIMAP_CENTER + 5,
			MINIMAP_RADIUS - 5, co.color);
	co.y += (MINIMAP_SIZE - 30);
	draw_map(game->map.map, game, co);
	draw_player(game);
}
