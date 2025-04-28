/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:58:00 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/28 15:44:28 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	fire(int button, int x, int y, t_data *g)
{
	(void)x;
	(void)y;
	if (button == 1 && !g->weapon.is_anim)
	{
		g->weapon.is_firing = true;
		g->weapon.is_anim = true;
		g->weapon.current_img = 0;
	}
	return (0);
}

static void	get_weapon_bob(t_data *g)
{
	if (g->p.up || g->p.down || g->p.left || g->p.right)
	{
		g->weapon.bob_x = cosf(g->weapon.bob_steps) * 2.0f;
		g->weapon.bob_y = fabsf(sinf(g->weapon.bob_steps)) * 2.0f;
		if (!g->p.run)
			g->weapon.bob_steps += 0.15f;
		else
			g->weapon.bob_steps += 0.25f;
		if (g->weapon.bob_steps > 2.0f * PI)
			g->weapon.bob_steps -= 2.0f * PI;
	}
	else
	{
		g->flag.bobbing = 0.0f;
		g->flag.bob_steps = 0.0f;
	}
}

void	weapon_anim(t_data *g)
{
	t_coord	co;

	if (g->weapon.is_firing)
	{
		g->weapon.anim_timer += g->delta_time;
		if (g->weapon.anim_timer >= 0.03)
		{
			g->weapon.anim_timer = 0;
			g->weapon.current_img++;
			if (g->weapon.current_img >= 7)
			{
				g->weapon.current_img = 0;
				g->weapon.is_firing = false;
				g->weapon.is_anim = false;
			}
		}
	}
	co.x = WIDTH / 2 - g->weapon.weapon[g->weapon.current_img].width;
	co.y = HEIGHT - g->weapon.weapon[g->weapon.current_img].height * 2;
	get_weapon_bob(g);
	co.x += g->weapon.bob_x;
	co.y += g->weapon.bob_y;
	draw_xpm(g, &g->weapon.weapon[g->weapon.current_img], co, 2);
}
