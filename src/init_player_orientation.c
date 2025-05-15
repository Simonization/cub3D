/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player_orientation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:27:28 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 22:37:11 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
