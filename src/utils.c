/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:34 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 22:35:42 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	ft_exit(int n, char *message, t_map *map)
{
	if (map)
	{
		if (map->no_path)
			free(map->no_path);
		if (map->so_path)
			free(map->so_path);
		if (map->we_path)
			free(map->we_path);
		if (map->ea_path)
			free(map->ea_path);
		if (map->line_len)
			free(map->line_len);
		if (map->map)
			free_array(map->map);
	}
	if (message)
		p_err(message);
	exit(n);
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
