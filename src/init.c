/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:53:03 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 18:01:51 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	get_map(void)
{
	t_map	map;
	int		i;

	i = -1;
	map.ceiling_color = 0x00451CCB;
	map.floor_color = 0x00361997;
	map.no_path = ft_strdup("img/among-us-yellow-shakes-booty.xpm");
	if (!map.no_path)
		return (printf("no path\n"), map);
	map.so_path = ft_strdup("img/among-us-red-shakes-booty.xpm");
	if (!map.so_path)
		return (printf("so path\n"), map);
	map.we_path = ft_strdup("img/among-us-purple-shakes-booty.xpm");
	if (!map.we_path)
		return (printf("we path\n"), map);
	map.ea_path = ft_strdup("img/among-us-green-shakes-booty.xpm");
	if (!map.ea_path)
		return (printf("ea path\n"), map);
	map.map = malloc(sizeof(char *) * 11);
	map.map[0] = ft_strdup("111111111111111111");
	map.map[1] = ft_strdup("101000000000000001");
	map.map[2] = ft_strdup("101000000000011111");
	map.map[3] = ft_strdup("1000000010000000011111111");
	map.map[4] = ft_strdup("10000000000000000000000001");
	map.map[5] = ft_strdup("10000000000000000000000001");
	map.map[6] = ft_strdup("1111100100000000011111111");
	map.map[7] = ft_strdup("100000110000000001");
	map.map[8] = ft_strdup("100000100000000001");
	map.map[9] = ft_strdup("111111111111111111");
	map.map[10] = NULL;
	map.line_len = malloc(sizeof(int) * 11);
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
	{
		printf("pas de img\n");
		ft_close(game);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp,
		&mlx->img.size_line, &mlx->img.endian);
	mlx->no.img = mlx_xpm_file_to_image(mlx->mlx, game->map.no_path, &mlx->no.width, &mlx->no.height);
	if (!mlx->no.img)
	{
		printf("pas de so\n");
		ft_close(game);
	}
	mlx->no.addr = mlx_get_data_addr(mlx->no.img, &mlx->no.bpp, &mlx->no.size_line, &mlx->no.endian);
	mlx->so.img = mlx_xpm_file_to_image(mlx->mlx, game->map.so_path, &mlx->so.width, &mlx->so.height);
	if (!mlx->so.img)
	{
		printf("pas de so\n");
		ft_close(game);
	}
	mlx->so.addr = mlx_get_data_addr(mlx->so.img, &mlx->so.bpp, &mlx->so.size_line, &mlx->so.endian);
	mlx->we.img = mlx_xpm_file_to_image(mlx->mlx, game->map.we_path, &mlx->we.width, &mlx->we.height);
	if (!mlx->we.img)
	{
		printf("pas de we\n");
		ft_close(game);
	}
	mlx->we.addr = mlx_get_data_addr(mlx->we.img, &mlx->we.bpp, &mlx->we.size_line, &mlx->we.endian);
	mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx, game->map.ea_path, &mlx->ea.width, &mlx->ea.height);
	if (!mlx->ea.img)
	{
		printf("pas de ea\n");
		ft_close(game);
	}
	mlx->ea.addr = mlx_get_data_addr(mlx->ea.img, &mlx->ea.bpp, &mlx->ea.size_line, &mlx->ea.endian);
}

void	player_init(t_player *player)
{
	player->co.x = WIDTH / 2;
	player->co.y = HEIGHT / 2;
	player->co.color = 0x0000FF00;
	player->angle = PI / 2;
	player->up = false;
	player->down = false;
	player->right = false;
	player->left = false;
	player->rotate_left = false;
	player->rotate_right = false;
}
