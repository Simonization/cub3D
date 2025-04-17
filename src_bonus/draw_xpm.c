/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_xpm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:35:48 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 22:37:24 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_coord	s_xpm(t_coord dst, t_coord incr, unsigned int color)
{
	t_coord	co;

	co.x = dst.x + incr.x;
	co.y = dst.y + incr.y;
	co.color = color;
	return (co);
}

void	draw_xpm(t_data *g, t_img *i, t_coord dst, int scale)
{
	t_coord			incr;
	t_coord			img_px;
	unsigned int	c;
	char			*px;

	img_px.y = 0;
	incr.y = 0;
	while (incr.y < i->height * scale)
	{
		img_px.x = 0;
		incr.x = 0;
		while (incr.x < i->width * scale)
		{
			px = i->addr + (img_px.y * i->size_line + img_px.x * i->bpp_8);
			c = *(unsigned int *)px;
			if (c != 0xFF000000)
				draw_square(s_xpm(dst, incr, c), scale, true, &g->mlx.img);
			incr.x += scale;
			img_px.x++;
		}
		incr.y += scale;
		img_px.y++;
	}
}
