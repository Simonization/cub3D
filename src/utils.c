/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:14:34 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/28 16:29:19 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
