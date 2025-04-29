/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:55:22 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 19:08:57 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int populate_map_structure(t_parse_buffer *buffer, t_map *temp_map, t_map *final_map)
{
    int i;
    int map_lines;
    
    (void)buffer;
    map_lines = 0;
    while (temp_map->map && temp_map->map[map_lines])
        map_lines++;
    
    if (map_lines == 0)
        return (print_error("No map data found"));
    final_map->map = malloc(sizeof(char *) * (map_lines + 1));
    if (!final_map->map)
        return (memory_error("map allocation"));
    final_map->line_len = malloc(sizeof(int) * map_lines);
    if (!final_map->line_len)
    {
        free(final_map->map);
        final_map->map = NULL;
        return (memory_error("line_len allocation"));
    }
    i = 0;
    while (i < map_lines)
    {
        final_map->map[i] = ft_strdup(temp_map->map[i]);
        if (!final_map->map[i])
        {
            clean_map_data(final_map);
            return (memory_error("map row duplication"));
        }
        final_map->line_len[i] = ft_strlen(final_map->map[i]);
        i++;
    }
    final_map->map[i] = NULL;
    final_map->no_path = ft_strdup(temp_map->no_path);
    final_map->so_path = ft_strdup(temp_map->so_path);
    final_map->we_path = ft_strdup(temp_map->we_path);
    final_map->ea_path = ft_strdup(temp_map->ea_path);
    
    if (!final_map->no_path || !final_map->so_path || 
        !final_map->we_path || !final_map->ea_path)
    {
        clean_map_data(final_map);
        return (memory_error("texture path duplication"));
    }
    final_map->ceiling_color = temp_map->ceiling_color;
    final_map->floor_color = temp_map->floor_color;
    return (1);
}