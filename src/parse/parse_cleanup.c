/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:38 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 19:06:05 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    cleanup_buffer(t_parse_buffer *buffer)
{
    int i;
    
    if (!buffer || !buffer->lines)
        return;
    
    i = 0;
    while (i < buffer->line_count && buffer->lines[i])
    {
        free(buffer->lines[i]);
        i++;
    }
    free(buffer->lines);
    buffer->lines = NULL;
    buffer->line_count = 0;
}

void    clean_map_data(t_map *map)
{
    int i;
    
    if (!map)
        return;
        
    if (map->map)
    {
        i = 0;
        while (map->map[i])
        {
            free(map->map[i]);
            i++;
        }
        free(map->map);
        map->map = NULL;
    }
    
    if (map->line_len)
    {
        free(map->line_len);
        map->line_len = NULL;
    }
    
    if (map->no_path)
        free(map->no_path);
    if (map->so_path)
        free(map->so_path);
    if (map->we_path)
        free(map->we_path);
    if (map->ea_path)
        free(map->ea_path);
    
    map->no_path = NULL;
    map->so_path = NULL;
    map->we_path = NULL;
    map->ea_path = NULL;
    map->ceiling_color = 0;
    map->floor_color = 0;
}

void    cleanup_parser_resources(t_parse_buffer *buffer, 
                                t_map *temp_map, 
                                t_map *final_map)
{
    if (buffer)
        cleanup_buffer(buffer);
    
    if (temp_map)
        clean_map_data(temp_map);
    
    if (final_map)
        clean_map_data(final_map);
}