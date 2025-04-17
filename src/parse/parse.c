/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:18:34 by slangero          #+#    #+#             */
/*   Updated: 2025/04/17 02:17:34 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int init_parser(t_display *display)
{
	display->mapboleen = 0;
	display->initsuccess = 0;
	display->textnum = 0;
	display->errorbool = 0;
	display->maptofree = -1;
	display->south = NULL;
	display->north = NULL;
	display->west = NULL;
	display->east = NULL;
	display->spritepwd = NULL;
	display->filename = NULL;
	return (0);
}

int parse_map(int argc, char *str, t_parse *parse, t_display *display)
{
	int     fd;
	size_t  str_len;

	if (argc == 3)
		display->bmp = 1;
	else
		display->bmp = 0;
		
	str_len = strlentoend(str);
	if ((display->filename = malloc(sizeof(char) * (str_len + 1))) == NULL)
		return (showerror(display, "Unable to Malloc"));
	
	if (checkcubextension(str, display) != 1)
		return (0);
		
	ft_strlcpy(display->filename, str, str_len + 1);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (showerror(display, "Unable to open file"));
		
	display->fd = fd;
	if (checkparse(display, parse, fd) != 0)
		return (0);
		
	return (1);
}

void init_player_position(t_data *game, t_display *display)
{
	game->player.co.x = display->player_x * BLOCK_SIZE;
	game->player.co.y = display->player_y * BLOCK_SIZE;
	
	if (display->dirx == 1)
		game->player.angle = 0;
	else if (display->dirx == -1)
		game->player.angle = PI;
	else if (display->diry == 1)
		game->player.angle = PI / 2;
	else if (display->diry == -1)
		game->player.angle = 3 * PI / 2;
	
	game->player.co.color = 0x0000FF00;
	game->player.up = false;
	game->player.down = false;
	game->player.right = false;
	game->player.left = false;
	game->player.rotate_left = false;
	game->player.rotate_right = false;
}

