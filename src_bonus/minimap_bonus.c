/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:09:40 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/12 23:58:06 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_square(t_coord co, int size, bool full, t_img *img)
{
	int	size_y;
	int	size_x;
	int	x_origin;
	int	y_origin;

	x_origin = co.x;
	y_origin = co.y;
	size_y = size;
	while(size_y)
	{
		co.x = x_origin;
		size_x = size;
		while (size_x)
		{
			if (full ||
				co.x == x_origin || co.x == x_origin + size - 1 ||
				co.y == y_origin || co.y == y_origin + size - 1)
				put_pixel(img, co.x, co.y, co.color);
			co.x++;
			size_x--;
		}
		co.y++;
		size_y--;
	}
}

void	draw_player(t_coord co, t_data *game)
{
	(void)co;
	t_coord	new_co;

	new_co.x = MINIMAP_CENTER;
	new_co.y = new_co.x;
	new_co.color = 0x00000000;
	draw_square(new_co, TILES_SIZE, true, &game->mlx.img);
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
		co2.y = ((co.y - (game->player.co.y / BLOCK_SIZE))
			* TILES_SIZE) + MINIMAP_CENTER;
		if (co2.y >= limit.x && co2.y < limit.y)
		{
			while (map[co.y][co.x])
			{
				co2.x = ((co.x - (game->player.co.x / BLOCK_SIZE))
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
	draw_player(co, game);
}
