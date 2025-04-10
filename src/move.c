/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 23:43:51 by agoldber         ###   ########.fr       */
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

void	move_direction(t_player *player, t_map map, float dx, float dy)
{
	float	len;
	float	new_x;
	float	new_y;

	len = sqrt(dx * dx + dy * dy);
	if (len > 0.001f)
	{
		dx = dx / len * SPEED;
		dy = dy / len * SPEED;
	}
	else
		return ;
	new_x = player->co.x + dx;
	new_y = player->co.y + dy;
	if (!is_wall(new_x, player->co.y, map))
		player->co.x = new_x;
	if (!is_wall(player->co.x, new_y, map))
		player->co.y = new_y;
}

void	change_d(float *dx, float *dy, float cos_a, float sin_a)
{
	*dx += cos_a;
	*dy -= sin_a;
}

void	move_player(t_player *p, t_map map)
{
	float	rotation_speed;
	float	dx;
	float	dy;

	rotation_speed = 0.1f;
	if (p->rotate_left)
		p->angle += rotation_speed;
	if (p->rotate_right)
		p->angle -= rotation_speed;
	if (p->angle > 2.0f * PI)
		p->angle = 0.0f;
	if (p->angle < 0.0f)
		p->angle = 2.0f * PI;
	dx = 0.0f;
	dy = 0.0f;
	if (p->up)
		change_d(&dx, &dy, cosf(p->angle), sinf(p->angle));
	if (p->down)
		change_d(&dx, &dy, -(cosf(p->angle)), -(sinf(p->angle)));
	if (p->right)
		change_d(&dx, &dy, cosf(p->angle - PI / 2), sinf(p->angle - PI / 2));
	if (p->left)
		change_d(&dx, &dy, cosf(p->angle + PI / 2), sinf(p->angle + PI / 2));
	move_direction(p, map, dx, dy);
}
