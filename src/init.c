/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:53:03 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/09 18:43:03 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_utils(t_data *game)
{
	game->trigo.cos_a = cosf(game->p.angle);
	game->trigo.sin_a = sinf(game->p.angle);
	game->trigo.cos_r = cosf(game->p.angle + PI / 2);
	game->trigo.sin_r = sinf(game->p.angle + PI / 2);
	game->trigo.cos_l = cosf(game->p.angle - PI / 2);
	game->trigo.sin_l = sinf(game->p.angle - PI / 2);
	game->fov = PI / 3.0f;
	game->fov_2 = game->fov / 2.0f;
	game->ray_steps = game->fov / WIDTH;
	game->projection = ((WIDTH / 2.0f) / tan(game->fov_2));
}

t_coord	get_player_pos(t_map map)
{
	t_coord	pos;

	pos.y = 0;
	pos.orientation = '\0';
	while (map.map[pos.y])
	{
		pos.x = 0;
		while (map.map[pos.y][pos.x])
		{
			if (ft_strchr("NSEW", map.map[pos.y][pos.x]))
			{
				pos.orientation = map.map[pos.y][pos.x];
				return (pos);
			}
			pos.x++;
		}
		pos.y++;
	}
	ft_putstr_fd("Error\nPlayer position not found by get_player_pos\n", 2);
	pos.x = -1;
	pos.y = -1;
	pos.orientation = '\0';
	return (pos);
}

void	player_init(t_player *p, t_coord start_pos_info)
{
	p->pos_x = (start_pos_info.x + 0.5f) * BLOCK_SIZE;
	p->pos_y = (start_pos_info.y + 0.5f) * BLOCK_SIZE;
	p->co.color = 0x0000FF00;
	if (start_pos_info.orientation == 'N')
	{
		p->angle = PI / 2.0f;
		p->dir_x = 0.0f;
		p->dir_y = -1.0f;
		p->plane_x = 0.66f;
		p->plane_y = 0.0f;
	}
	else if (start_pos_info.orientation == 'S')
	{
		p->angle = 3.0f * PI / 2.0f;
		p->dir_x = 0.0f;
		p->dir_y = 1.0f;
		p->plane_x = -0.66f;
		p->plane_y = 0.0f;
	}
	else if (start_pos_info.orientation == 'E')
	{
		p->angle = 0.0f;
		p->dir_x = 1.0f;
		p->dir_y = 0.0f;
		p->plane_x = 0.0f;
		p->plane_y = 0.66f;
	}
	else if (start_pos_info.orientation == 'W')
	{
		p->angle = PI;
		p->dir_x = -1.0f;
		p->dir_y = 0.0f;
		p->plane_x = 0.0f;
		p->plane_y = -0.66f;
	}
	else
	{
		ft_putstr_fd(
			"Warning: player_init: invalid orient.Default to North.\n", 2);
		p->angle = PI / 2.0f;
		p->dir_x = 0.0f;
		p->dir_y = -1.0f;
		p->plane_x = 0.66f;
		p->plane_y = 0.0f;
	}
	p->up = false;
	p->down = false;
	p->right = false;
	p->left = false;
	p->rotate_left = false;
	p->rotate_right = false;
}
