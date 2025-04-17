/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:34 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 22:40:54 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	delta(float *dx, float *dy, float cos_a, float sin_a)
{
	*dx += cos_a;
	*dy -= sin_a;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	put_fps(t_data *game)
{
	struct timeval	now;
	float			delta;
	float			since_last_print;

	gettimeofday(&now, NULL);
	delta = (now.tv_sec - game->last_time.tv_sec)
		+ (now.tv_usec - game->last_time.tv_usec) / 1000000.0f;
	game->delta_time = delta;
	if (delta > 0.0f)
		game->fps = 1.0f / delta;
	game->last_time = now;
	since_last_print = (now.tv_sec - game->last_fps_print.tv_sec)
		+ (now.tv_usec - game->last_fps_print.tv_usec) / 1000000.0f;
	if (since_last_print >= 0.2f)
	{
		printf("FPS: %.2f\n", game->fps);
		game->last_fps_print = now;
	}
}

void	change_fov(t_data *g)
{
	float	speed;

	speed = 0.009f;
	if (g->flag.crouch)
		g->target_fov = PI / 3.5f;
	else if (g->p.run)
	{
		g->target_fov = PI / 2.5f;
		speed = 0.015;
	}
	else
		g->target_fov = PI / 3.0f;
	if (g->fov < g->target_fov)
		g->fov += speed;
	else if (g->fov > g->target_fov)
		g->fov -= speed;
	if (fabsf(g->fov - g->target_fov) < speed)
		g->fov = g->target_fov;
	g->fov_2 = g->fov / 2.0f;
	g->ray_steps = g->fov / WIDTH;
	g->projection = ((WIDTH / 2.0f) / tanf(g->fov_2));
}
