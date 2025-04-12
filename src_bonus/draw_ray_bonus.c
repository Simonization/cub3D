/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:46:18 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/11 20:40:54 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_texture(int y, t_img texture, int top, t_ray ray)
{
	int		t_x;
	float	t_y_ratio;
	int		t_y;
	char	*px;

	if (ray.v_hit)
		t_x = ((int)ray.x % BLOCK_SIZE) * texture.width / BLOCK_SIZE;
	else
		t_x = ((int)ray.y % BLOCK_SIZE) * texture.width / BLOCK_SIZE;
	if (t_x < 0)
		t_x = 0;
	else if (t_x >= texture.width)
		t_x = texture.width - 1;
	t_y_ratio = (y - top) / (float)ray.wall_height;
	t_y = t_y_ratio * texture.height;
	if (t_y < 0)
		t_y = 0;
	else if (t_y >= texture.height)
		t_y = texture.height - 1;
	px = texture.addr + (t_y * texture.size_line + t_x * (texture.bpp / 8));
	return (*(unsigned int *)px);
}

int	orientation(t_data *g, int y, int top)
{
	if (g->ray.v_hit)
	{
		if (g->ray.sin_a > 0.0f)
			return (get_texture(y, g->mlx.no, top, g->ray));
		else
			return (get_texture(y, g->mlx.so, top, g->ray));
	}
	else
	{
		if (g->ray.cos_a > 0.0f)
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
	if (g->ray.wall_height > HEIGHT * 5)
		g->ray.wall_height = HEIGHT * 5;
	start = HEIGHT - g->ray.wall_height / 2 - (360 - g->flag.head_offset);
	end = start + g->ray.wall_height;
	while (i++ <= start)
		put_pixel(&g->mlx.img, g->ray.column, i, g->map.ceiling_color);
	i = start;
	while (start++ < end)
		put_pixel(&g->mlx.img, g->ray.column, start, orientation(g, start, i));
	while (start++ < HEIGHT)
		put_pixel(&g->mlx.img, g->ray.column, start, g->map.floor_color);
}

void	slice_of_wall(t_data *g, int i)
{
	g->ray.cos_a = cosf(g->ray.a);
	g->ray.sin_a = sinf(g->ray.a);
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
			if (touch(g->ray.old_x, g->ray.y, g->map)
				&& !touch(g->ray.x, g->ray.old_y, g->map))
				g->ray.v_hit = true;
			draw_walls(g, distance(g->player, g->ray));
			return ;
		}
		i++;
	}
}

void	draw_ray(t_data *g)
{
	g->ray.a = g->player.angle + (FOV / 2.0f);
	g->ray.column = 0;
	while (g->ray.a >= g->player.angle - (FOV / 2.0f))
	{
		slice_of_wall(g, 0);
		g->ray.a -= (FOV / (WIDTH - 10));
		g->ray.column++;
	}
}
