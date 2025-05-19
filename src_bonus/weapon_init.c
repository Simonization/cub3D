/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 01:59:17 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/19 02:20:20 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	weapon_error(char *to_free, t_data *g)
{
	ft_putstr_fd("Error\nWeapon init\n", 2);
	if (to_free)
		free(to_free);
	ft_close(g);
}

static char	*get_texture_name(t_data *g, int i)
{
	char	*name;
	char	*temp;

	name = ft_itoa(i + 1);
	if (!name)
		return (weapon_error(NULL, g), NULL);
	temp = ft_strjoin("img/w", name);
	if (!temp)
		return (weapon_error(name, g), NULL);
	free(name);
	name = ft_strjoin(temp, ".xpm");
	if (!name)
		return (weapon_error(temp, g), NULL);
	free(temp);
	return (name);
}

void	weapon_init(t_data *g)
{
	int		i;
	char	*name;

	i = -1;
	while (++i < 7)
		g->weapon.weapon[i].img = NULL;
	i = 0;
	g->weapon.current_img = 0;
	g->weapon.is_firing = false;
	g->weapon.is_anim = false;
	g->weapon.anim_timer = 0.0;
	while (i <= 6)
	{
		name = get_texture_name(g, i);
		g->weapon.weapon[i].img = mlx_xpm_file_to_image(g->mlx.mlx,
				name, &g->weapon.weapon[i].width, &g->weapon.weapon[i].height);
		free(name);
		if (!g->weapon.weapon[i].img)
			return (weapon_error(NULL, g));
		g->weapon.weapon[i].addr = mlx_get_data_addr(
				g->weapon.weapon[i].img, &g->weapon.weapon[i].bpp,
				&g->weapon.weapon[i].size_line, &g->weapon.weapon[i].endian);
		g->weapon.weapon[i].bpp_8 = g->weapon.weapon[i].bpp / 8;
		i++;
	}
}
