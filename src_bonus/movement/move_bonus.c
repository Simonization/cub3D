/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 01:08:14 by agoldber         ###   ########.fr       */
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
	if (player->run)
		speed = 10;
	len = sqrt(dx * dx + dy * dy);
	if (len < 0.001f)
		return ;
	// printf("angle du joueur : %f\n", player->angle);
	// printf("avant len\ndx : %f\ndy : %f\n", dx, dy);
	dx = dx * speed;
	dy = dy * speed;
	// printf("apres len\ndx : %f\ndy : %f\n", dx, dy);
	move_buffer(player, map, dx, dy);
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
	if (g->p.angle >= 2.0f * PI)
		g->p.angle -= 2.0f * PI;
	else if (g->p.angle < 0.0f)
		g->p.angle += 2.0f * PI;
	g->trigo.cos_a = cosf(g->p.angle);
	g->trigo.sin_a = -sinf(g->p.angle);
	g->trigo.cos_r = cosf(g->p.angle + PI / 2);
	g->trigo.sin_r = -sinf(g->p.angle + PI / 2);
	g->trigo.cos_l = cosf(g->p.angle - PI / 2);
	g->trigo.sin_l = -sinf(g->p.angle - PI / 2);
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
		delta(&dx, &dy, g->trigo.cos_l, g->trigo.sin_l);
	if (g->p.left)
		delta(&dx, &dy, g->trigo.cos_r, g->trigo.sin_r);
	move_direction(&g->p, &g->map, dx, dy);
}
