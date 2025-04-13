/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:44:45 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/13 23:00:44 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	touch(float x, float y, t_map map)
{
	int		x_ray;
	int		y_ray;
	char	tile;

	x_ray = (int)(x / BLOCK_SIZE);
	y_ray = (int)(y / BLOCK_SIZE);
	if (x_ray < 0 || y_ray < 0 || !map.map[y_ray]
		|| x_ray >= map.line_len[y_ray])
		return (1);
	tile = map.map[y_ray][x_ray];
	return (tile == '1');
}

float	distance(t_player player, t_ray r, float disto)
{
	float	delta_x;
	float	delta_y;
	float	distortion;

	delta_x = (player.co.x - r.x) * (player.co.x - r.x);
	delta_y = (player.co.y - r.y) * (player.co.y - r.y);
	distortion = sqrt(delta_x + delta_y);
	return (distortion * disto);
}
