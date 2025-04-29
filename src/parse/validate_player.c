/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:32:14 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 18:34:10 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

typedef struct s_player_init {
    int     pos_x;
    int     pos_y;
    char    orientation;
    float   angle;
    float   dir_x;
    float   dir_y;
    float   plane_x;
    float   plane_y;
} t_player_init;

static int find_player_data(t_map *map, t_player_init *player_data)
{
    int i;
    int j;
    int player_count;

    player_count = 0;
    i = 0;
    while (map->map[i])
    {
        j = 0;
        while (j < map->line_len[i])
        {
            if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
                map->map[i][j] == 'E' || map->map[i][j] == 'W')
            {
                if (player_count > 0)
                    return (0);
                player_data->pos_x = j;
                player_data->pos_y = i;
                player_data->orientation = map->map[i][j];
                player_count++;
            }
            j++;
        }
        i++;
    }
    return (player_count);
}

static void set_player_orientation(t_player_init *player_data)
{
    if (player_data->orientation == 'N')
    {
        player_data->angle = 3 * PI / 2;
        player_data->dir_x = 0;
        player_data->dir_y = -1;
        player_data->plane_x = 0.66;
        player_data->plane_y = 0;
    }
    else if (player_data->orientation == 'S')
    {
        player_data->angle = PI / 2;
        player_data->dir_x = 0;
        player_data->dir_y = 1;
        player_data->plane_x = -0.66;
        player_data->plane_y = 0;
    }
    else if (player_data->orientation == 'E')
    {
        player_data->angle = 0;
        player_data->dir_x = 1;
        player_data->dir_y = 0;
        player_data->plane_x = 0;
        player_data->plane_y = 0.66;
    }
    else if (player_data->orientation == 'W')
    {
        player_data->angle = PI;
        player_data->dir_x = -1;
        player_data->dir_y = 0;
        player_data->plane_x = 0;
        player_data->plane_y = -0.66;
    }
}

int init_player_from_map(t_map *map, t_player *player)
{
    t_player_init player_data;
    
    if (find_player_data(map, &player_data) != 1)
        return (ft_putstr_fd("Error\nInvalid player position in map\n", 2), 0);
    set_player_orientation(&player_data);
    map->map[player_data.pos_y][player_data.pos_x] = '0';
    player->pos_x = (player_data.pos_x + 0.5f) * BLOCK_SIZE;
    player->pos_y = (player_data.pos_y + 0.5f) * BLOCK_SIZE;
    player->co.x = player_data.pos_x;
    player->co.y = player_data.pos_y;
    player->co.color = 0x0000FF00;
    player->angle = player_data.angle;
    player->dir_x = player_data.dir_x;
    player->dir_y = player_data.dir_y;
    player->plane_x = player_data.plane_x;
    player->plane_y = player_data.plane_y;
    player->up = false;
    player->down = false;
    player->right = false;
    player->left = false;
    player->rotate_left = false;
    player->rotate_right = false;
    return (1);
}