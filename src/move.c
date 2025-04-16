/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/16 18:13:40 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(float x, float y, t_map *map)
{
	int	x_map;
	int	y_map;

	x_map = x / BLOCK_SIZE;
	y_map = y / BLOCK_SIZE;
	if (y_map < 0 || !map->map[y_map] || x_map < 0
		|| x_map >= map->line_len[y_map] || !map->map[y_map][x_map])
		return (1);
	return (map->map[y_map][x_map] == '1');
}

void	move_buffer(t_player *p, t_map *map, float dx, float dy)
{
	int	buffer;
	int	new_x;
	int	new_y;

	new_x = p->co.x + dx;
	new_y = p->co.y + dy;
	if (dx != 0.0f)
	{
		if (dx > 0)
			buffer = 2;
		else
			buffer = -2;
		if (!is_wall(new_x + buffer, p->co.y, map))
			p->co.x = new_x;
	}
	if (dy != 0.0f)
	{
		if (dy > 0)
			buffer = 2;
		else
			buffer = -2;
		if (!is_wall(p->co.x, new_y + buffer, map))
			p->co.y = new_y;
	}
}

void	move_direction(t_player *player, t_map *map, float dx, float dy)
{
	float	len;
	int		speed;

	speed = 5;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.001f)
		return ;
	dx = dx / len * speed;
	dy = dy / len * speed;
	move_buffer(player, map, dx, dy);
}

void	rotation(t_data *g)
{
	float	rotation_speed;

	rotation_speed = 0.05f;
	if (g->player.rotate_left)
		g->player.angle += rotation_speed;
	if (g->player.rotate_right)
		g->player.angle -= rotation_speed;
	if (g->player.angle > 2.0f * PI)
		g->player.angle = 0.0f;
	if (g->player.angle < 0.0f)
		g->player.angle = 2.0f * PI;
	g->trigo.cos_a = cosf(g->player.angle);
	g->trigo.sin_a = sinf(g->player.angle);
	g->trigo.cos_r = cosf(g->player.angle + PI / 2);
	g->trigo.sin_r = sinf(g->player.angle + PI / 2);
	g->trigo.cos_l = cosf(g->player.angle - PI / 2);
	g->trigo.sin_l = sinf(g->player.angle - PI / 2);
}

void	move_player(t_data *g)
{
	float	dx;
	float	dy;

	rotation(g);
	dx = 0.0f;
	dy = 0.0f;
	if (g->player.up)
		delta(&dx, &dy, g->trigo.cos_a, g->trigo.sin_a);
	if (g->player.down)
		delta(&dx, &dy, -g->trigo.cos_a, -(g->trigo.sin_a));
	if (g->player.right)
		delta(&dx, &dy, g->trigo.cos_l, g->trigo.sin_l);
	if (g->player.left)
		delta(&dx, &dy, g->trigo.cos_r, g->trigo.sin_r);
	move_direction(&g->player, &g->map, dx, dy);
}
