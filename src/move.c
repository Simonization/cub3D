/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 16:47:47 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(float x, float y, t_map map)
{
	int	x_map;
	int	y_map;

	x_map = x / BLOCK_SIZE;
	y_map = y / BLOCK_SIZE;
	if (y_map < 0 || !map.map[y_map] || x_map < 0
		|| x_map > (int)ft_strlen(map.map[y_map]) || !map.map[y_map][x_map])
		return (1);
	return (map.map[y_map][x_map] == '1');
}

void	move_direction(t_player *player, t_map map, int speed, float angle)
{
	float	cos_a;
	float	sin_a;
	float	new_x;
	float	new_y;

	cos_a = cos(angle);
	sin_a = sin(angle);
	new_x = (player->co.x + cos_a * (speed + P_SIZE));
	new_y = (player->co.y - sin_a * (speed + P_SIZE));
	if (!is_wall(new_x, player->co.y, map))
		player->co.x = player->co.x + cos_a * (speed + P_SIZE - 2);
	if (!is_wall(player->co.x, new_y, map))
		player->co.y = player->co.y - sin_a * (speed + P_SIZE - 2);
}

void	move_player(t_player *player, t_map map)
{
	int		speed;
	float	rotation_speed;

	speed = 5;
	rotation_speed = 0.1;
	if (player->rotate_left)
		player->angle += rotation_speed;
	if (player->rotate_right)
		player->angle -= rotation_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	// if (player->up && player->down)
		// return ;
	// if (player->left && player->right)
		// 	return ;
	if (player->up)
		move_direction(player, map, speed, player->angle);
	if (player->down)
		move_direction(player, map, speed, player->angle - PI);
	if (player->right)
		move_direction(player, map, speed, player->angle - PI / 2);
	if (player->left)
		move_direction(player, map, speed, player->angle + PI / 2);
}
