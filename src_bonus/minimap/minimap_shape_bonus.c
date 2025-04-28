/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_shape_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:46:38 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/28 15:42:22 by agoldber         ###   ########.fr       */
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
	while (size_y)
	{
		co.x = x_origin;
		size_x = size;
		while (size_x)
		{
			if (full
				|| co.x == x_origin || co.x == x_origin + size - 1
				|| co.y == y_origin || co.y == y_origin + size - 1)
				put_pixel(img, co.x, co.y, co.color);
			co.x++;
			size_x--;
		}
		co.y++;
		size_y--;
	}
}

static void	part_triangle(int x, int y, t_img *img)
{
	int	dx;
	int	dy;

	dx = 0;
	while (dx <= 1)
	{
		dy = 0;
		while (dy <= 1)
		{
			put_pixel(img, x + dx, y + dy, 0x00FF0000);
			dy++;
		}
		dx++;
	}
}

void	draw_triangle_side(t_trigo a, t_trigo perp, t_img *img)
{
	t_coord	iter;
	t_coord	base;
	t_coord	line;
	int		depth;

	depth = 0;
	iter.x = 0;
	while (iter.x < 8)
	{
		base.x = MINIMAP_PLAYER + perp.cos_a * iter.x;
		base.y = MINIMAP_PLAYER - perp.sin_a * iter.x;
		iter.y = 0;
		while (iter.y < TILES_SIZE - depth)
		{
			line.x = base.x + a.cos_a * iter.y;
			line.y = base.y - a.sin_a * iter.y;
			part_triangle(line.x, line.y, img);
			iter.y++;
		}
		iter.x++;
		depth += 2;
	}
}
