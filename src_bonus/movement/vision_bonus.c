/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vision.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:21:21 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/13 16:21:44 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	offset(t_flag *f, t_player *player)
{
	if (f->head_up && !player->run)
		f->head_offset += 10;
	if (f->head_up && player->run)
		f->head_offset += 15;
	if (f->head_down && !player->run)
		f->head_offset -= 10;
	if (f->head_down && player->run)
		f->head_offset -= 15;
	if (f->head_offset > 360)
		f->head_offset = 360;
	if (f->head_offset < -360)
		f->head_offset = -360;
	if (f->jump)
	{
		f->jump_time += 0.1f;
		f->jump_offset = sinf(f->jump_time) * 4.5f;
		if (f->jump_time >= PI)
		{
			f->jump_offset = 0.0f;
			f->jump_time = 0.0f;
			f->jump = false;
		}
	}
}

void	bobbing(t_data *game)
{
	if (game->p.up || game->p.down || game->p.left || game->p.right)
	{
		game->flag.bobbing = sinf(game->flag.bob_steps) * 2.0f;
		if (!game->p.run)
			game->flag.bob_steps += 0.15f;
		else
			game->flag.bob_steps += 0.25f;
		game->flag.head_offset += game->flag.bobbing;
		if (game->flag.bob_steps > 2.0f * PI)
			game->flag.bob_steps -= 2.0f * PI;
	}
	else
	{
		game->flag.bobbing = 0.0f;
		game->flag.bob_steps = 0.0f;
	}
}
