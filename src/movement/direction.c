/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:34:32 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/28 15:34:42 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	move_player_forward(t_data *g, float speed)
{
	float	new_x;
	float	new_y;

	new_x = g->p.pos_x + g->p.dir_x * speed;
	new_y = g->p.pos_y + g->p.dir_y * speed;
	validate_move(g, new_x, new_y);
}

void	move_player_backward(t_data *g, float speed)
{
	float	new_x;
	float	new_y;

	new_x = g->p.pos_x - g->p.dir_x * speed;
	new_y = g->p.pos_y - g->p.dir_y * speed;
	validate_move(g, new_x, new_y);
}

void	move_player_left(t_data *g, float speed)
{
	float	new_x;
	float	new_y;

	new_x = g->p.pos_x + g->p.dir_y * speed;
	new_y = g->p.pos_y - g->p.dir_x * speed;
	validate_move(g, new_x, new_y);
}

void	move_player_right(t_data *g, float speed)
{
	float	new_x;
	float	new_y;

	new_x = g->p.pos_x - g->p.dir_y * speed;
	new_y = g->p.pos_y + g->p.dir_x * speed;
	validate_move(g, new_x, new_y);
}
