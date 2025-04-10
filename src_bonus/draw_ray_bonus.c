/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:46:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 18:43:33 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

int	get_texture(int y, t_img texture, int top, t_ray ray)
{
	int		texture_x;
	float	texture_y_ratio;
	int		texture_y;
	char	*pixel;

	if (ray.v_hit)
		texture_x = ((int)ray.x % BLOCK_SIZE) * texture.width / BLOCK_SIZE;
	else
		texture_x = ((int)ray.y % BLOCK_SIZE) * texture.width / BLOCK_SIZE;
	if (texture_x < 0)
		texture_x = 0;
	else if (texture_x >= texture.width)
		texture_x = texture.width - 1;
	texture_y_ratio = (y - top) / (float)ray.wall_height;
	texture_y = texture_y_ratio * texture.height;		
	if (texture_y < 0)
		texture_y = 0;
	else if (texture_y >= texture.height)
		texture_y = texture.height - 1;
	pixel = texture.addr + (texture_y * texture.size_line + texture_x * (texture.bpp / 8));
	return (*(unsigned int *)pixel);
}

int	get_orientation(t_data *g, int y, int top)
{
	if (g->ray.v_hit)
	{
		if (g->ray.sin_a > 0)
			return (get_texture(y, g->mlx.no, top, g->ray));
		else
			return (get_texture(y, g->mlx.so, top, g->ray));
	}
	else
	{
		if (g->ray.cos_a > 0)
			return (get_texture(y, g->mlx.ea, top, g->ray));
		else
			return (get_texture(y, g->mlx.we, top, g->ray));
	}
}

void	draw_walls(t_data *g, float wall_distance)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	g->ray.wall_height = (BLOCK_SIZE / wall_distance) * PROJECTION;
	start = (HEIGHT / 2) - (g->ray.wall_height / 2);
	end = start + g->ray.wall_height;
	while (i <= start)
	{
		put_pixel(&g->mlx.img, g->ray.column, i, g->map.ceiling_color);
		i++;
	}
	i = start;
	while (start < end)
	{
		put_pixel(&g->mlx.img, g->ray.column, start, get_orientation(g, start, i));
		start++;
	}
	while (start < HEIGHT)
	{
		put_pixel(&g->mlx.img, g->ray.column, start, g->map.floor_color);
		start++;
	}
}

void	slice_of_wall(t_data *g, int i)
{
	g->ray.cos_a = cos(g->ray.a);
	g->ray.sin_a = sin(g->ray.a);
	g->ray.x = g->player.co.x;
	g->ray.y = g->player.co.y;
	while (1)
	{
		g->ray.v_hit = false;
		g->ray.old_x = g->ray.x;
		g->ray.old_y = g->ray.y;
		g->ray.x = (g->player.co.x) + g->ray.cos_a * i;
		g->ray.y = (g->player.co.y) - g->ray.sin_a * i;
		if (touch(g->ray.x, g->ray.y, g->map))
		{
			if (touch(g->ray.old_x, g->ray.y, g->map) && !touch(g->ray.x, g->ray.old_y, g->map))
			g->ray.v_hit = true;
			draw_walls(g, distance(g->player, g->ray));
			return ;
		}
		i++;
	}
}

void	draw_ray(t_data *g)
{
	g->ray.a = g->player.angle + (FOV / 2);
	g->ray.column = 0;
	while (g->ray.a >= g->player.angle - (FOV / 2))
	{
		slice_of_wall(g, 0);
		g->ray.a -= (FOV / (WIDTH - 10));
		g->ray.column++;
	}
}
