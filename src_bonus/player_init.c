/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 01:57:29 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/19 02:03:04 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	north_orientation(t_player *p)
{
	p->angle = PI / 2.0f;
	p->dir_x = 0.0f;
	p->dir_y = -1.0f;
	p->plane_x = 0.66f;
	p->plane_y = 0.0f;
}

void	south_orientation(t_player *p)
{
	p->angle = 3.0f * PI / 2.0f;
	p->dir_x = 0.0f;
	p->dir_y = 1.0f;
	p->plane_x = -0.66f;
	p->plane_y = 0.0f;
}

void	east_orientation(t_player *p)
{
	p->angle = 0.0f;
	p->dir_x = 1.0f;
	p->dir_y = 0.0f;
	p->plane_x = 0.0f;
	p->plane_y = 0.66f;
}

void	west_orientation(t_player *p)
{
	p->angle = PI;
	p->dir_x = -1.0f;
	p->dir_y = 0.0f;
	p->plane_x = 0.0f;
	p->plane_y = -0.66f;
}
