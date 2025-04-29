/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:25 by slangero          #+#    #+#             */
/*   Updated: 2025/04/29 19:06:49 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     print_error(char *message)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd("\n", 2);
    return (0);
}

int     file_error(char *filename)
{
    ft_putstr_fd("Error\nCould not open file: ", 2);
    ft_putstr_fd(filename, 2);
    ft_putstr_fd("\n", 2);
    return (0);
}

int     memory_error(char *context)
{
    ft_putstr_fd("Error\nMemory allocation failed", 2);
    if (context)
    {
        ft_putstr_fd(" during ", 2);
        ft_putstr_fd(context, 2);
    }
    ft_putstr_fd("\n", 2);
    return (0);
}

int     syntax_error(int line_num, char *detail)
{
    ft_putstr_fd("Error\nSyntax error", 2);
    if (line_num >= 0)
    {
        ft_putstr_fd(" at line ", 2);
        ft_putnbr_fd(line_num, 2);
    }
    if (detail)
    {
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(detail, 2);
    }
    ft_putstr_fd("\n", 2);
    return (0);
}

int     parse_error_cleanup(t_parse_buffer *buffer, 
                           t_map *temp_map, 
                           t_map *final_map, 
                           char *message)
{
    cleanup_parser_resources(buffer, temp_map, final_map);
    return (print_error(message));
}