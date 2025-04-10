/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:09:40 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/09 17:09:45 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	draw_square(t_coord co, int size, bool full, t_img *img)
// {
// 	int	size_y;
// 	int	size_x;
// 	int	x_origin;
// 	int	y_origin;

// 	x_origin = co.x;
// 	y_origin = co.y;
// 	size_y = size;
// 	while(size_y)
// 	{
// 		co.x = x_origin;
// 		size_x = size;
// 		while (size_x)
// 		{
// 			if (full ||
// 				co.x == x_origin || co.x == x_origin + size - 1 ||
// 				co.y == y_origin || co.y == y_origin + size - 1)
// 				put_pixel(img, co.x, co.y, co.color);
// 			co.x++;
// 			size_x--;
// 		}
// 		co.y++;
// 		size_y--;
// 	}
// }

// void	draw_player(t_coord co, t_img *img)
// {
// 	co.x -= P_SIZE / 2;
// 	co.y -= P_SIZE / 2;
// 	draw_square(co, P_SIZE, true, img);
// }

// void	draw_map(char **map, t_img *img)
// {
// 	t_coord	co;
// 	t_coord	co2;

// 	co2.color = 0x00FA00FA;
// 	co.y = 0;
// 	while (map[co.y])
// 	{
// 		co.x = 0;
// 		co2.y = co.y * BLOCK_SIZE;
// 		while (map[co.y][co.x])
// 		{
// 			co2.x = co.x * BLOCK_SIZE;
// 			if (map[co.y][co.x] == '1')
// 				draw_square(co2, BLOCK_SIZE, false, img);
// 			co.x++;
// 		}
// 		co.y++;
// 	}
// }

// void	draw_direction(t_player *player, t_img *img, char **map)
// {
// 	int i = 0;
// 	int max_len = 100;
// 	int x;
// 	int	y;

// 	(void)map;
// 	while (i < max_len)
// 	{
// 		x = (player->co.x + 5) + cos(player->angle) * i;
// 		y = (player->co.y + 5) - sin(player->angle) * i;
// 		put_pixel(img, x, y, 0x00FF0000);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < max_len)
// 	{
// 		x = (player->co.x + 5) + cos(player->angle - PI / 2) * i;
// 		y = (player->co.y + 5) - sin(player->angle - PI / 2) * i;
// 		put_pixel(img, x, y, 0x000000FF);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < max_len)
// 	{
// 		x = (player->co.x + 5) + cos(player->angle + PI / 2) * i;
// 		y = (player->co.y + 5) - sin(player->angle + PI / 2) * i;
// 		put_pixel(img, x, y, 0x0000FF00);
// 		i++;
// 	}
// }