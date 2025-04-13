/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/13 02:34:06 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_wall(float x, float y, t_map *map)
{
	int	x_map;
	int	y_map;

	x_map = x / BLOCK_SIZE;
	y_map = y / BLOCK_SIZE;
	if (y_map < 0 || !map->map[y_map] || x_map < 0
		|| x_map > map->line_len[y_map] || !map->map[y_map][x_map])
		return (1);
	return (map->map[y_map][x_map] == '1');
}

void	move_direction(t_player *player, t_map *map, float dx, float dy)
{
	float	len;
	float	new_x;
	float	new_y;
	int		speed;

	speed = 5;
	if (player->run)
		speed = 10;
	len = sqrt(dx * dx + dy * dy);
	if (len > 0.001f)
	{
		dx = dx / len * speed;
		dy = dy / len * speed;
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

void	delta(float *dx, float *dy, float cos_a, float sin_a)
{
	*dx += cos_a;
	*dy -= sin_a;
}

void	rotation(t_data *g)
{
	float	rotation_speed;

	rotation_speed = 0.05f;
	if (g->p.run)
		rotation_speed += 0.03f;
	if (g->p.rotate_left)
		g->p.angle += rotation_speed;
	if (g->p.rotate_right)
		g->p.angle -= rotation_speed;
	if (g->p.angle > 2.0f * PI)
		g->p.angle = 0.0f;
	if (g->p.angle < 0.0f)
		g->p.angle = 2.0f * PI;
	g->trigo.cos_a = cosf(g->p.angle);
	g->trigo.sin_a = sinf(g->p.angle);
}

void	move_player(t_data *g)
{
	float	dx;
	float	dy;

	rotation(g);
	dx = 0.0f;
	dy = 0.0f;
	if (g->p.up)
		delta(&dx, &dy, g->trigo.cos_a, g->trigo.sin_a);
	if (g->p.down)
		delta(&dx, &dy, -g->trigo.cos_a, -(g->trigo.sin_a));
	if (g->p.right)
		delta(&dx, &dy, cosf(g->p.angle - PI / 2), sinf(g->p.angle - PI / 2));
	if (g->p.left)
		delta(&dx, &dy, cosf(g->p.angle + PI / 2), sinf(g->p.angle + PI / 2));
	move_direction(&g->p, &g->map, dx, dy);
}
