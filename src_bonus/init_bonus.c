/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:53:03 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/19 01:59:29 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	get_no_so_img(t_mlx *mlx, t_data *game)
{
	mlx->no.img = mlx_xpm_file_to_image(mlx->mlx,
			game->map.no_path, &mlx->no.width, &mlx->no.height);
	if (!mlx->no.img)
		ft_close(game);
	mlx->no.addr = mlx_get_data_addr(mlx->no.img,
			&mlx->no.bpp, &mlx->no.size_line, &mlx->no.endian);
	mlx->no.bpp_8 = mlx->no.bpp / 8;
	mlx->no.steps = mlx->no.width / BLOCK_SIZE;
	mlx->so.img = mlx_xpm_file_to_image(mlx->mlx,
			game->map.so_path, &mlx->so.width, &mlx->so.height);
	if (!mlx->so.img)
		ft_close(game);
	mlx->so.addr = mlx_get_data_addr(mlx->so.img,
			&mlx->so.bpp, &mlx->so.size_line, &mlx->so.endian);
	mlx->so.bpp_8 = mlx->so.bpp / 8;
	mlx->so.steps = mlx->so.width / BLOCK_SIZE;
}

void	get_we_ea_img(t_mlx *mlx, t_data *game)
{
	mlx->we.img = mlx_xpm_file_to_image(mlx->mlx,
			game->map.we_path, &mlx->we.width, &mlx->we.height);
	if (!mlx->we.img)
		ft_close(game);
	mlx->we.addr = mlx_get_data_addr(mlx->we.img,
			&mlx->we.bpp, &mlx->we.size_line, &mlx->we.endian);
	mlx->we.bpp_8 = mlx->we.bpp / 8;
	mlx->we.steps = mlx->we.width / BLOCK_SIZE;
	mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx,
			game->map.ea_path, &mlx->ea.width, &mlx->ea.height);
	if (!mlx->ea.img)
		ft_close(game);
	mlx->ea.addr = mlx_get_data_addr(mlx->ea.img,
			&mlx->ea.bpp, &mlx->ea.size_line, &mlx->ea.endian);
	mlx->ea.bpp_8 = mlx->ea.bpp / 8;
	mlx->ea.steps = mlx->ea.width / BLOCK_SIZE;
}

void	windows_init(t_mlx *mlx, t_data *game)
{
	if (!game)
		exit(1);
	if (!game->map.no_path)
		exit(1);
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		ft_close(game);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
			&mlx->img.size_line, &mlx->img.endian);
	game->img_size = HEIGHT * game->mlx.img.size_line;
	get_no_so_img(mlx, game);
	get_we_ea_img(mlx, game);
}

void	player_init(t_player *p, t_coord pos)
{
	p->pos_x = (pos.x + 0.5f) * BLOCK_SIZE;
	p->pos_y = (pos.y + 0.5f) * BLOCK_SIZE;
	p->co.color = 0x0000FF00;
	if (pos.orientation == 'N')
		north_orientation(p);
	else if (pos.orientation == 'S')
		south_orientation(p);
	else if (pos.orientation == 'E')
		east_orientation(p);
	else if (pos.orientation == 'W')
		west_orientation(p);
	p->up = false;
	p->down = false;
	p->right = false;
	p->left = false;
	p->rotate_left = false;
	p->rotate_right = false;
	p->run = false;
}

void	init_utils(t_data *game)
{
	game->flag.head_offset = 0;
	game->flag.head_up = false;
	game->flag.head_down = false;
	game->flag.bobbing = 0.0f;
	game->flag.bob_steps = 0.0f;
	game->flag.jump_offset = 0.0f;
	game->flag.jump = false;
	game->flag.crouch = false;
	game->flag.crouch_time = 0.0f;
	game->flag.map = 1;
	game->trigo.cos_a = cosf(game->p.angle);
	game->trigo.sin_a = sinf(game->p.angle);
	game->trigo.cos_r = cosf(game->p.angle + PI / 2);
	game->trigo.sin_r = sinf(game->p.angle + PI / 2);
	game->trigo.cos_l = cosf(game->p.angle - PI / 2);
	game->trigo.sin_l = sinf(game->p.angle - PI / 2);
	gettimeofday(&game->last_time, NULL);
	gettimeofday(&game->last_fps_print, NULL);
	game->fps = 0.0f;
	game->fov = PI / 3.0f;
	game->fov_2 = game->fov / 2.0f;
	game->tan_fov = tan(game->fov_2);
	game->ray_steps = game->fov / WIDTH;
	game->projection = ((WIDTH / 2.0f) / tan(game->fov_2));
	game->target_fov = PI / 3.5f;
}
