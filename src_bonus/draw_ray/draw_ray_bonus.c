/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:46:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/30 18:26:32 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	init_dda(t_data *g)
{
	g->ray.pos_x = g->p.pos_x;
	g->ray.pos_y = g->p.pos_y;
	g->ray.camera_x = 2.0 * g->ray.col / WIDTH - 1.0;
	g->ray.dir_x = g->p.dir_x + g->p.plane_x * g->ray.camera_x;
	g->ray.dir_y = g->p.dir_y + g->p.plane_y * g->ray.camera_x;
	g->ray.map_x = (int)(g->p.pos_x / BLOCK_SIZE);
	g->ray.map_y = (int)(g->p.pos_y / BLOCK_SIZE);
	if (g->ray.dir_x == 0)
		g->ray.delta_x = 1e30;
	else
		g->ray.delta_x = fabsf(1.0f / g->ray.dir_x);
	if (g->ray.dir_y == 0)
		g->ray.delta_y = 1e30;
	else
		g->ray.delta_y = fabsf(1.0f / g->ray.dir_y);
}

static void	init_dir(t_data *g)
{
	float	cell_x;
	float	cell_y;

	cell_x = g->p.pos_x / BLOCK_SIZE;
	cell_y = g->p.pos_y / BLOCK_SIZE;
	if (g->ray.dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x = (cell_x - g->ray.map_x) * g->ray.delta_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x = (g->ray.map_x + 1.0 - cell_x) * g->ray.delta_x;
	}
	if (g->ray.dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y = (cell_y - g->ray.map_y) * g->ray.delta_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y = (g->ray.map_y + 1.0 - cell_y) * g->ray.delta_y;
	}
}

static void	dda(t_data *g)
{
	g->ray.hit = false;
	while (!g->ray.hit)
	{
		if (g->ray.side_dist_x < g->ray.side_dist_y)
		{
			g->ray.side_dist_x += g->ray.delta_x;
			g->ray.map_x += g->ray.step_x;
			g->ray.side = 0;
		}
		else
		{
			g->ray.side_dist_y += g->ray.delta_y;
			g->ray.map_y += g->ray.step_y;
			g->ray.side = 1;
		}
		if (g->map.map[g->ray.map_y][g->ray.map_x] == '1')
			g->ray.hit = true;
	}
}

void	floor_and_ceiling(t_data *g)
{
	float	raydir_x0;
	float	raydir_y0;
	float	raydir_x1;
	float	raydir_y1;
	int		p;
	float	pos_z;
	float	row_distance;
	float	floorstep_x;
	float	floorstep_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		x;
	int		y;
	char	*pixel;
	int		color;

	y = 0;
	while (y < HEIGHT)
	{
		raydir_x0 = g->ray.dir_x - g->p.plane_x;
		raydir_y0 = g->ray.dir_y - g->p.plane_y;
		raydir_x1 = g->ray.dir_x + g->p.plane_x;
		raydir_y1 = g->ray.dir_y + g->p.plane_y;
		p = y - Y_CENTER;
		pos_z = 0.5 * HEIGHT; //g->flag.head_offset
		row_distance = pos_z / p;
		floorstep_x = row_distance * (raydir_x1 - raydir_x0) / WIDTH;
		floorstep_y = row_distance * (raydir_y1 - raydir_y0) / WIDTH;
		floor_x = g->p.pos_x + row_distance * raydir_x0;
		floor_y = g->p.pos_y + row_distance * raydir_y0;
		x = 0;
		while (x < WIDTH)
		{
			cell_x = (int)floor_x;
			cell_y = (int)floor_y;
			tx = (int)(g->mlx.ea.width * (floor_x - cell_x)) & (g->mlx.ea.width - 1);
			ty = (int)(g->mlx.ea.height * (floor_y - cell_y)) & (g->mlx.ea.height - 1);
			floor_x += floorstep_x;
			floor_y += floorstep_y;
			pixel = g->mlx.ea.addr + (ty * g->mlx.ea.size_line + tx * (g->mlx.ea.bpp_8));
			color = *(int *)pixel;
			put_pixel(&g->mlx.img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_ray(t_data *g)
{
	g->ray.col = 0;
	floor_and_ceiling(g);
	while (g->ray.col < WIDTH)
	{
		init_dda(g);
		init_dir(g);
		dda(g);
		if (g->ray.side == 0)
			g->ray.wall_dist = (g->ray.side_dist_x - g->ray.delta_x);
		else
			g->ray.wall_dist = (g->ray.side_dist_y - g->ray.delta_y);
		g->ray.hit_x = (g->p.pos_x / BLOCK_SIZE)
			+ g->ray.wall_dist * g->ray.dir_x;
		g->ray.hit_y = (g->p.pos_y / BLOCK_SIZE)
			+ g->ray.wall_dist * g->ray.dir_y;
		if (g->ray.side == 0)
			g->ray.wall_x = g->ray.hit_y;
		else
			g->ray.wall_x = g->ray.hit_x;
		g->ray.wall_x -= floorf(g->ray.wall_x);
		draw_walls(g, g->ray.wall_dist);
		g->ray.col++;
	}
}
