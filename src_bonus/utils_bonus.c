/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:34 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/12 00:54:15 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	destroy_images(t_data *game)
{
	int	i;

	game->weapon.current_img = 0;
	i = 0;
	while (game->weapon.weapon[i].img)
	{
		mlx_destroy_image(game->mlx.mlx, game->weapon.weapon[i].img);
		i++;
	}
	if (game->mlx.mlx && game->mlx.img.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img.img);
	if (game->mlx.mlx && game->mlx.no.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.no.img);
	if (game->mlx.mlx && game->mlx.so.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.so.img);
	if (game->mlx.mlx && game->mlx.we.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.we.img);
	if (game->mlx.mlx && game->mlx.ea.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.ea.img);
}

int	ft_close(t_data *game)
{
	destroy_images(game);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	free_array(game->map.map);
	if (game->map.no_path)
		free(game->map.no_path);
	if (game->map.so_path)
		free(game->map.so_path);
	if (game->map.we_path)
		free(game->map.we_path);
	if (game->map.ea_path)
		free(game->map.ea_path);
	free(game->map.line_len);
	exit(0);
	return (0);
}
