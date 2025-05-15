/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:44:12 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 14:49:56 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1600
# define HEIGHT 900
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define P 112
# define LEFT 65361
# define RIGHT 65363
# define BLOCK_SIZE 64
# define PI 3.14159265359f
# define RAY_STEPS (FOV / WIDTH)
# define PROJECTION ((WIDTH / 2) / tan(FOV / 2.0f))
# define X_CENTER WIDTH / 2
# define Y_CENTER HEIGHT / 2

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		bpp_8;
	int		size_line;
	int		endian;
	int		width;
	float	steps;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_mlx;

typedef struct s_coordinates
{
	int		x;
	int		y;
	char	orientation;
	int		color;
}	t_coord;

typedef struct s_ray
{
	int		col;
	float	wall_height;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	camera_x;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	int		step_x;
	int		step_y;
	float	delta_x;
	float	delta_y;
	bool	side;
	bool	hit;
	float	wall_dist;
	float	hit_x;
	float	hit_y;
	float	wall_x;
}	t_ray;

typedef	struct s_player
{
	t_coord	co;
	float	angle;
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	rotate_left;
	bool	rotate_right;
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		*line_len;
	int		ceiling_color;
	int		floor_color;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		no_path_set;
	int		so_path_set;
	int		we_path_set;
	int		ea_path_set;
	int		floor_color_set;
	int		ceiling_color_set;
    int     map_height;
    int     map_width;
}	t_map;

typedef struct s_trigo
{
	float	cos_a;
	float	sin_a;
	float	cos_r;
	float	sin_r;
	float	cos_l;
	float	sin_l;
}	t_trigo;

typedef struct s_data
{
	t_mlx			mlx;
	t_player		p;
	t_trigo			trigo;
	t_ray			ray;
	t_map			map;
	float			fov;
	float			fov_2;
	float			ray_steps;
	float			projection;
	float			target_fov;
	int				img_size;
}	t_data;

// PARSING FUNCTIONS
int parsing_error(const char *msg);
t_map	parse_map(char *file_path);
int		is_map_line(char *line);
int		extract_map_data(char **lines, t_map *map, int map_content_start_index);
void	initialize_map_config_flags(t_map *map);
int		count_lines(char *file_path);
int		is_valid_xpm_path(const char *path);

// MAP VALIDATION
int		validate_player_position(t_map *map);
int		validate_map_walls(t_map *map);
int     validate_map(t_map *map);

// RGB VALIDATION
int		process_f_color(t_map *map, char *value_part);
int		process_c_color(t_map *map, char *value_part);
int     is_valid_rgb_component(char *component);
int		parse_and_validate_rgb(char *rgb_string);
int		assign_rgb_color(int *map_color_field, const char *value_str, int *is_set_flag);

// TEXTURE VALIDATION
int	assign_texture_path(char **map_texture_path, const char *path_value, int *is_set_flag);
int	parse_texture_and_color_paths(char **lines, t_map *map, int *map_content_start_index);
int process_no_texture(t_map *map, char *value_part);
int process_so_texture(t_map *map, char *value_part);
int process_we_texture(t_map *map, char *value_part);
int process_ea_texture(t_map *map, char *value_part);



// UTILS
void	put_pixel(t_img *img, int x, int y, int color);
void	free_array(char **arr);
// char	*get_next_line(int fd);
void	ft_exit(int n, char *message, t_map *map);
void	print_error(char *message);

// INIT FUNCTIONS
void	windows_init(t_mlx *mlx, t_data *game);
t_coord	get_player_pos(t_map map);
void	player_init(t_player *player, t_coord start_pos_info);
void	init_utils(t_data *game);

// HOOKS and GAME LOOP
int		pressed_key(int keycode, t_data *game);
int		released_key(int keycode, t_data *game);
int		ft_close(t_data *game);

// MOVEMENT
void	move_player(t_data *g);
void	validate_move(t_data *g, float new_x, float new_y);
void	move_player_forward(t_data *g, float speed);
void	move_player_backward(t_data *g, float speed);
void	move_player_left(t_data *g, float speed);
void	move_player_right(t_data *g, float speed);

// DRAWING
void	draw_ray(t_data *game);
void	draw_walls(t_data *g, float wall_distance);

#endif