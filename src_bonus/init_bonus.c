/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:53:03 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/30 14:41:10 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_map	get_map(void)
{
	t_map	map;
	int		i;

	i = -1;
	map.ceiling_color = 0x00303030;
	map.floor_color = 0x00303030;
	// map.no_path = ft_strdup("img/among-us-yellow-shakes-booty.xpm");
	// if (!map.no_path)
	// 	return (printf("no path\n"), map);
	// map.so_path = ft_strdup("img/among-us-red-shakes-booty.xpm");
	// if (!map.so_path)
	// 	return (printf("so path\n"), map);
	// map.we_path = ft_strdup("img/among-us-purple-shakes-booty.xpm");
	// if (!map.we_path)
	// 	return (printf("we path\n"), map);
	// map.ea_path = ft_strdup("img/among-us-green-shakes-booty.xpm");
	map.no_path = ft_strdup("img/mossy.xpm");
	if (!map.no_path)
		return (printf("no path\n"), map);
	map.so_path = ft_strdup("img/mossy.xpm");
	if (!map.so_path)
		return (printf("so path\n"), map);
	map.we_path = ft_strdup("img/greystone.xpm");
	if (!map.we_path)
		return (printf("we path\n"), map);
	map.ea_path = ft_strdup("img/greystone.xpm");
	if (!map.ea_path)
		return (printf("ea path\n"), map);
	map.map = malloc(sizeof(char *) * 54);
	map.map[0] = ft_strdup("                             1111111111111");
	map.map[1] = ft_strdup("     111111                  1000000000001");
	map.map[2] = ft_strdup("     100001      11111111111110000000000011111");
	map.map[3] = ft_strdup("     100001      10000000000010000000000010001");
	map.map[4] = ft_strdup("     1000001     10000000000000000000000000001");
	map.map[5] = ft_strdup("     1000001     10001111111110000000000010001");
	map.map[6] = ft_strdup("     11111111111010001       10000000000011111");
	map.map[7] = ft_strdup("     1000000000101000111      111110111111");
	map.map[8] = ft_strdup("     1000000000111000001         10001");
	map.map[9] = ft_strdup("     1000000000100000001         10001");
	map.map[10] = ft_strdup("     1000000000000000001         10001");
	map.map[11] = ft_strdup("     1000000000111111111         10001");
	map.map[12] = ft_strdup("     10000000001            111111000111");
	map.map[13] = ft_strdup("1111110000000001            100000000001");
	map.map[14] = ft_strdup("100011111101111             100111000111");
	map.map[15] = ft_strdup("1000110010001               1001110001");
	map.map[16] = ft_strdup("1000100010001               1001110001");
	map.map[17] = ft_strdup("1101100010001               1111110001");
	map.map[18] = ft_strdup("1000111110001                    10001");
	map.map[19] = ft_strdup("1000111010001                    11011                11111111");
	map.map[20] = ft_strdup("1000011011011111           111111000001111111         10000001");
	map.map[21] = ft_strdup("1000011000000001           100000000000000011         10000001");
	map.map[22] = ft_strdup("1000000000000001           10000000000000001111111111110000001");
	map.map[23] = ft_strdup("1000001000000001           10000000000000000100000000010000001");
	map.map[24] = ft_strdup("1000011000000001           10000000P00000000000000000000000001");
	map.map[25] = ft_strdup("1000011000000001           10000000000000000100000000010000001");
	map.map[26] = ft_strdup("1000011000000001           10000000000000001111000011110000001");
	map.map[27] = ft_strdup("10000111111011111          100000000000000011111001   10000001");
	map.map[28] = ft_strdup("10000111110001             11111100000111111   1001   10000001");
	map.map[29] = ft_strdup("10000111110001                  111011         1001   11111111");
	map.map[30] = ft_strdup("10000100010001                   10001         1001");
	map.map[31] = ft_strdup("10000000010001                   10001         1001");
	map.map[32] = ft_strdup("10000100010001                   10001         100111111111111");
	map.map[33] = ft_strdup("10000111110001                   10001         100010000000001");
	map.map[34] = ft_strdup("10000111110001111111111111       10001         100000000000001");
	map.map[35] = ft_strdup("1000000000000000001000000111     10001         100010000000001");
	map.map[36] = ft_strdup("1000000000000000000000000101     10001         111111111111111");
	map.map[37] = ft_strdup("1000000000000000001000000111     10001");
	map.map[38] = ft_strdup("11111111111111111111111111       10001");
	map.map[39] = ft_strdup("           11001001001      111111101111111");
	map.map[40] = ft_strdup("          11000100101       100001000100001");
	map.map[41] = ft_strdup("           110000011        100000000000001");
	map.map[42] = ft_strdup("            111111          100001000100001");
	map.map[43] = ft_strdup("            1001            100001000100001");
	map.map[44] = ft_strdup("            1001            111111000111111");
	map.map[45] = ft_strdup("            1111            100001000100001");
	map.map[46] = ft_strdup("                            100000000000001");
	map.map[47] = ft_strdup("                            100001000100001");
	map.map[48] = ft_strdup("                            111111000111111");
	map.map[49] = ft_strdup("                            100000000000001");
	map.map[50] = ft_strdup("                            100000000000001");
	map.map[51] = ft_strdup("                            100000000000001");
	map.map[52] = ft_strdup("                            111111111111111");
	map.map[53] = NULL;
	map.line_len = malloc(sizeof(int) * 54);
	while (map.map[++i])
		map.line_len[i] = ft_strlen(map.map[i]);
	return (map);
}

void	windows_init(t_mlx *mlx, t_data *game)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3d");
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		ft_close(game);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
		&mlx->img.size_line, &mlx->img.endian);
	game->img_size = HEIGHT * game->mlx.img.size_line;
	mlx->no.img = mlx_xpm_file_to_image(mlx->mlx, game->map.no_path, &mlx->no.width, &mlx->no.height);
	if (!mlx->no.img)
		ft_close(game);
	mlx->no.addr = mlx_get_data_addr(mlx->no.img, &mlx->no.bpp, &mlx->no.size_line, &mlx->no.endian);
	mlx->no.bpp_8 = mlx->no.bpp / 8;
	mlx->no.steps = mlx->no.width / BLOCK_SIZE;
	mlx->so.img = mlx_xpm_file_to_image(mlx->mlx, game->map.so_path, &mlx->so.width, &mlx->so.height);
	if (!mlx->so.img)
		ft_close(game);
	mlx->so.addr = mlx_get_data_addr(mlx->so.img, &mlx->so.bpp, &mlx->so.size_line, &mlx->so.endian);
	mlx->so.bpp_8 = mlx->so.bpp / 8;
	mlx->so.steps = mlx->so.width / BLOCK_SIZE;
	mlx->we.img = mlx_xpm_file_to_image(mlx->mlx, game->map.we_path, &mlx->we.width, &mlx->we.height);
	if (!mlx->we.img)
		ft_close(game);
	mlx->we.addr = mlx_get_data_addr(mlx->we.img, &mlx->we.bpp, &mlx->we.size_line, &mlx->we.endian);
	mlx->we.bpp_8 = mlx->we.bpp / 8;
	mlx->we.steps = mlx->we.width / BLOCK_SIZE;
	mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx, game->map.ea_path, &mlx->ea.width, &mlx->ea.height);
	if (!mlx->ea.img)
		ft_close(game);
	mlx->ea.addr = mlx_get_data_addr(mlx->ea.img, &mlx->ea.bpp, &mlx->ea.size_line, &mlx->ea.endian);
	mlx->ea.bpp_8 = mlx->ea.bpp / 8;
	mlx->ea.steps = mlx->ea.width / BLOCK_SIZE;
}

t_coord	get_player_pos(t_map map)
{
	t_coord	pos;

	pos.y = 0;
	while (map.map[pos.y])
	{
		pos.x = 0;
		while (map.map[pos.y][pos.x])
		{
			if (map.map[pos.y][pos.x] == 'P')
				return (pos);
			pos.x++;
		}
		pos.y++;
	}
	return (pos);
}

void	player_init(t_player *p, t_coord pos)
{
	p->pos_x = (pos.x + 0.5f) * BLOCK_SIZE;
	p->pos_y = (pos.y + 0.5f) * BLOCK_SIZE;
	p->co.color = 0x0000FF00;
	p->angle = PI / 2;
	p->dir_x = cosf(p->angle);
	p->dir_y = -sinf(p->angle);
	p->plane_x = 0.66;
	p->plane_y = 0;
	p->angle = atan2(-p->dir_y, p->dir_x);
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

void	weapon_init(t_data *game)
{
	int	i;
	char	*path;
	char	*name;
	char	*extension;
	char	*all;

	i = 0;
	path = ft_strdup("img/w");
	extension = ft_strdup(".xpm");
	game->weapon.current_img = 0;
	game->weapon.is_firing = false;
	game->weapon.is_anim = false;
	game->weapon.anim_timer = 0.0;
	while (i <= 6)
	{
		name = ft_itoa(i + 1);
		all = ft_strjoin(path, name);
		free(name);
		name = ft_strjoin(all, extension);
		free(all);
		game->weapon.weapon[i].img = mlx_xpm_file_to_image(game->mlx.mlx, name, &game->weapon.weapon[i].width, &game->weapon.weapon[i].height);
		game->weapon.weapon[i].addr = mlx_get_data_addr(game->weapon.weapon[i].img, &game->weapon.weapon[i].bpp, &game->weapon.weapon[i].size_line, &game->weapon.weapon[i].endian);
		game->weapon.weapon[i].bpp_8 = game->weapon.weapon[i].bpp / 8;
		free(name);
		i++;
	}
	free(path);
	free(extension);
}
