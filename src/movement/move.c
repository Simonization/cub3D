/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:49:19 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/09 18:45:19 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(float x, float y, t_map *map)
{
	int	x_map;
	int	y_map;

	x_map = (int)(x / BLOCK_SIZE);
	y_map = (int)(y / BLOCK_SIZE);
	if (y_map < 0 || !map->map[y_map] || x_map < 0
		|| x_map >= map->line_len[y_map] || !map->map[y_map][x_map])
		return (1);
	return (map->map[y_map][x_map] == '1');
}

inline static int	is_free(t_map *m, float x, float y)
{
	float	r;

	r = 10.0f;
	return (!is_wall(x + r, y + r, m) && !is_wall(x - r, y + r, m)
		&& !is_wall(x + r, y - r, m) && !is_wall(x - r, y - r, m));
}

void	validate_move(t_data *g, float new_x, float new_y)
{
	if (is_free(&g->map, new_x, g->p.pos_y))
		g->p.pos_x = new_x;
	if (is_free(&g->map, g->p.pos_x, new_y))
		g->p.pos_y = new_y;
}

static void	rotate_player(t_data *g)
{
	float	rotation_speed;

	rotation_speed = 0.05f;
	if (g->p.rotate_left)
		g->p.angle += rotation_speed;
	if (g->p.rotate_right)
		g->p.angle -= rotation_speed;
	if (g->p.angle > 2.0f * PI)
		g->p.angle = 0.0f;
	if (g->p.angle < 0.0f)
		g->p.angle = 2.0f * PI;
	g->p.dir_x = cosf(g->p.angle);
	g->p.dir_y = -sinf(g->p.angle);
	g->p.plane_x = -g->p.dir_y * tan(g->fov / 2);
	g->p.plane_y = g->p.dir_x * tan(g->fov / 2);
}

void	move_player(t_data *g)
{
	float	speed;

	speed = 5.0f;
	if (g->p.up)
		move_player_forward(g, speed);
	if (g->p.down)
		move_player_backward(g, speed);
	if (g->p.left)
		move_player_left(g, speed);
	if (g->p.right)
		move_player_right(g, speed);
	if (g->p.rotate_left || g->p.rotate_right)
		rotate_player(g);
	g->trigo.cos_a = g->p.dir_x;
	g->trigo.sin_a = -g->p.dir_y;
	g->trigo.cos_r = cosf(g->p.angle + PI / 2);
	g->trigo.sin_r = sinf(g->p.angle + PI / 2);
	g->trigo.cos_l = cosf(g->p.angle - PI / 2);
	g->trigo.sin_l = sinf(g->p.angle - PI / 2);
}

to rotate player
	// if (g->p.run)
		// rotation_speed += 0.03f;

//to run player
	// if (g->p.run && !g->flag.crouch)
		// speed = 10.0f;
	// else if (g->flag.crouch)
		// speed = 3.0f;