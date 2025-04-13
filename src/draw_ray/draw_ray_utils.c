/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:44:45 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 23:45:07 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	touch(float x, float y, t_map map)
{
	int	x_ray;
	int	y_ray;

	x_ray = x / BLOCK_SIZE;
	y_ray = y / BLOCK_SIZE;
	if (!map.map[y_ray] || x_ray < 0
		|| x_ray > map.line_len[y_ray] || !map.map[y_ray][x_ray])
		return (1);
	return (map.map[y_ray][x_ray] == '1');
}

float	distance(t_player player, t_ray r)
{
	float	delta_x;
	float	delta_y;
	float	distortion;

	delta_x = (player.co.x - r.x) * (player.co.x - r.x);
	delta_y = (player.co.y - r.y) * (player.co.y - r.y);
	distortion = sqrt(delta_x + delta_y);
	return (distortion * cos(r.a - player.angle));
}
