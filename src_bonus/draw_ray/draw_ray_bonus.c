/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:46:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/14 19:08:28 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_texture(t_img texture, int t_height, t_ray ray)
{
	int		t_x;
	int		t_y;
	char	*px;

	if (ray.v_hit)
		t_x = ((int)ray.x % BLOCK_SIZE) * texture.steps;
	else
		t_x = ((int)ray.y % BLOCK_SIZE) * texture.steps;
	if (t_x < 0)
		t_x = 0;
	else if (t_x >= texture.width)
		t_x = texture.width - 1;
	t_y = t_height / (int)ray.wall_height;
	if (t_y < 0)
		t_y = 0;
	else if (t_y >= texture.height)
		t_y = texture.height - 1;
	px = texture.addr + (t_y * texture.size_line + t_x * texture.bpp_8);
	return (*(unsigned int *)px);
}

int	orientation(t_data *g, int height)
{
	if (g->ray.v_hit)
	{
		if (g->ray.sin_a > 0.0f)
			return (get_texture(g->mlx.no, height * g->mlx.no.height, g->ray));
		else
			return (get_texture(g->mlx.so, height * g->mlx.so.height, g->ray));
	}
	else
	{
		if (g->ray.cos_a > 0.0f)
			return (get_texture(g->mlx.ea, height * g->mlx.ea.height, g->ray));
		else
			return (get_texture(g->mlx.we, height * g->mlx.we.height, g->ray));
	}
}

void	draw_walls(t_data *g, float wall_distance)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	g->ray.wall_height = (BLOCK_SIZE / wall_distance) * PROJECTION;
	if (g->ray.wall_height > HEIGHT * 5)
		g->ray.wall_height = HEIGHT * 5;
	start = HEIGHT - g->ray.wall_height / (2 + g->flag.jump_offset)
		- (360 - g->flag.head_offset);
	end = start + g->ray.wall_height;
	while (i++ <= start)
		put_pixel(&g->mlx.img, g->ray.column, i, g->map.ceiling_color);
	i = start;
	while (start++ < end)
		put_pixel(&g->mlx.img, g->ray.column, start, orientation(g, start - i));
	while (start++ < HEIGHT)
		put_pixel(&g->mlx.img, g->ray.column, start, g->map.floor_color);
}

void	slice_of_wall(t_data *g, int i)
{
	float	disto;

	g->ray.cos_a = cosf(g->ray.a);
	g->ray.sin_a = sinf(g->ray.a);
	disto = cosf(g->ray.a - g->p.angle);
	g->ray.x = g->p.co.x;
	g->ray.y = g->p.co.y;
	while (1)
	{
		g->ray.v_hit = false;
		g->ray.old_x = g->ray.x;
		g->ray.old_y = g->ray.y;
		g->ray.x = (g->p.co.x) + g->ray.cos_a * i;
		g->ray.y = (g->p.co.y) - g->ray.sin_a * i;
		if (touch(g->ray.x, g->ray.y, g->map))
		{
			if (touch(g->ray.old_x, g->ray.y, g->map)
				&& !touch(g->ray.x, g->ray.old_y, g->map))
				g->ray.v_hit = true;
			draw_walls(g, distance(g->p, g->ray, disto));
			return ;
		}
		i += 1;
	}
}

// void	dda(t_data *g)
// {
// 	float	ray_x;
// 	float	ray_y;
// 	float	ray_a;

// 	float	map_x;
// 	float	map_y;

// 	float	delta_x;
// 	float	delta_y;

// 	int		step_x;
// 	int		step_y;

// 	float	side_dist_x;
// 	float	side_dist_y;

// 	bool	side; //0 = VERTICAL | 1 = HORIZONTAL
// 	bool	hit;

// 	float	distance;

// 	ray_x = g->p.co.x;
// 	ray_y = g->p.co.y;
// 	ray_a = g->p.angle;

// 	map_x = ray_x / BLOCK_SIZE;
// 	map_y = ray_y / BLOCK_SIZE;

// 	delta_x = fabsf(BLOCK_SIZE / cosf(ray_a));
// 	delta_y = fabsf(BLOCK_SIZE / -sinf(ray_a));

// 	if (ray_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (g->p.co.x - map_x * BLOCK_SIZE) * delta_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = ((map_x + 1) * BLOCK_SIZE - g->p.co.x) * delta_x;
// 	}

// 	if (ray_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (g->p.co.y - map_y * BLOCK_SIZE) * delta_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = ((map_y + 1) * BLOCK_SIZE - g->p.co.y) * delta_y;
// 	}

// 	hit = false;
// 	while (!hit)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_x;
// 			map_x += step_x;
// 			side = VERTICAL;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_y;
// 			map_y += step_y;
// 			side = HORIZONTAL;
// 		}
// 		if (touch(map_x, map_y, g->map))
// 			hit = true;
// 	}
// 	if (side == VERTICAL)
// 		distance = (side_dist_x - delta_x) * cosf(ray_a - g->p.angle);
// 	else
// 		distance = (side_dist_y - delta_y) * cosf(ray_a - g->p.angle);
// 	draw_walls(g, distance);
// }

void	draw_ray(t_data *g)
{
	g->ray.a = g->p.angle + FOV_2;
	g->ray.column = 0;
	while (g->ray.a >= g->p.angle - FOV_2)
	{
		slice_of_wall(g, 0);
		// dda(g);
		g->ray.a -= RAY_STEPS;
		g->ray.column++;
	}
}
