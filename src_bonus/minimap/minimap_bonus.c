/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:09:40 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/13 02:55:36 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player(t_data *game)
{
	t_trigo	perp;

	perp.cos_a = cosf(game->p.angle - PI / 2);
	perp.sin_a = sinf(game->p.angle - PI / 2);
	draw_triangle_side(game->trigo, perp, &game->mlx.img);
	perp.cos_a = cosf(game->p.angle + PI / 2);
	perp.sin_a = sinf(game->p.angle + PI / 2);
	draw_triangle_side(game->trigo, perp, &game->mlx.img);
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
		if (co2.y >= limit.x && co2.y < limit.y)
		{
			while (map[co.y][co.x])
			{
				co2.x = ((co.x - (game->p.co.x / BLOCK_SIZE))
						* TILES_SIZE) + MINIMAP_CENTER;
				if (co2.x >= limit.x && co2.x < limit.y
					&& map[co.y][co.x] == '1')
					draw_square(co2, TILES_SIZE, true, &game->mlx.img);
				co.x++;
			}
		}
		co.y++;
	}
}

void	draw_minimap(t_data *game)
{
	t_coord	co;

	co.x = 10;
	co.y = 10;
	co.color = 0x00000000;
	draw_square(co, MINIMAP_SIZE, true, &game->mlx.img);
	co.x += 10;
	co.y += 10;
	co.color = 0x00FFFFFF;
	draw_square(co, MINIMAP_SIZE - 20, true, &game->mlx.img);
	co.y += (MINIMAP_SIZE - 30);
	draw_map(game->map.map, game, co);
	draw_player(game);
}
