/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:44:45 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/07 22:22:43 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	get_light(int color, float wall_distance)
{
	float	intensity;
	int		r;
	int		g;
	int		b;

	intensity = 1.0f / (wall_distance * 0.5f);
	if (intensity > 1.0f)
		intensity = 1.0f;
	r = (int)(((color >> 16) & 0xFF) * intensity);
	g = (int)(((color >> 8) & 0xFF) * intensity);
	b = (int)((color & 0xFF) * intensity);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

static int	get_texture(t_img tex, int height, t_ray ray)
{
	int		tex_x;
	int		tex_y;
	char	*pixel;
	int		color;
	float	step;

	tex_x = (int)(ray.wall_x * tex.width);
	if ((ray.side == 0 && ray.dir_x > 0) || (ray.side == 1 && ray.dir_y < 0))
		tex_x = tex.width - tex_x - 1;
	step = (float)tex.height / ray.wall_height;
	tex_y = (int)(height * step);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex.height)
		tex_y = tex.height - 1;
	pixel = tex.addr + (tex_y * tex.size_line + tex_x * (tex.bpp_8));
	color = *(int *)pixel;
	return (color);
}

static int	side_wall(t_data *g, int height)
{
	if (g->ray.side == 0)
	{
		if (g->ray.dir_x > 0.0f)
			return (get_texture(g->mlx.ea, height, g->ray));
		else
			return (get_texture(g->mlx.we, height, g->ray));
	}
	else
	{
		if (g->ray.dir_y > 0.0f)
			return (get_texture(g->mlx.so, height, g->ray));
		else
			return (get_texture(g->mlx.no, height, g->ray));
	}
}

t_coord	draw_walls(t_data *g, float wall_distance)
{
	int	i;
	int	start;
	int	end;
	t_coord	start_end;
	int	color;

	i = 0;
	color = 0;
	g->ray.wall_height = g->projection / wall_distance;
	start = HEIGHT - g->ray.wall_height / (2 + g->flag.jump_offset)
		- (360 - g->flag.head_offset);
	end = start + g->ray.wall_height;
	start_end.x = start;
	start_end.y = end;
	while (i++ <= start)
		put_pixel(&g->mlx.img, g->ray.col, i, g->map.ceiling_color);
	i = start;
	while (start++ < end)
	{
		if (start > 0 && start <= HEIGHT)
		{
			color = get_light(side_wall(g, start - i), wall_distance);
			put_pixel(&g->mlx.img, g->ray.col, start, color);
		}
	}
	while (start++ < HEIGHT)
		put_pixel(&g->mlx.img, g->ray.col, start, g->map.floor_color);
	return (start_end);
}
