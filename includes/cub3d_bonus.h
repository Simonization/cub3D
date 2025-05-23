/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:42:57 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/19 02:17:19 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define WIDTH 1600
# define HEIGHT 900
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define P 112
# define SPACE 32
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define SHIFT 65505
# define BLOCK_SIZE 64
# define PI 3.14159265359f
# define X_CENTER 800
# define Y_CENTER 450
# define MINIMAP_SIZE 160
# define TILES_SIZE 15
# define MINIMAP_RADIUS 84
# define MINIMAP_CENTER 83.75
# define MINIMAP_PLAYER 90
# define CROUCH 65507

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_img
{
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

typedef struct s_player
{
	t_coord	co;
	float	angle;
	bool	up;
	bool	down;
	bool	right;
	bool	left;
	bool	rotate_left;
	bool	rotate_right;
	bool	run;
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
}	t_map;

typedef struct s_flag
{
	int		head_offset;
	bool	head_up;
	bool	head_down;
	float	bobbing;
	float	bob_steps;
	float	jump_offset;
	float	jump_time;
	bool	jump;
	int		map;
	float	crouch_time;
	bool	crouch;
}	t_flag;

typedef struct s_trigo
{
	float	cos_a;
	float	sin_a;
	float	cos_r;
	float	sin_r;
	float	cos_l;
	float	sin_l;
}	t_trigo;

typedef struct s_weapon
{
	t_img	weapon[7];
	int		current_img;
	double	anim_timer;
	bool	is_firing;
	bool	is_anim;
	float	bob_x;
	float	bob_y;
	float	bob_steps;
}	t_weapon;

typedef struct s_data
{
	t_mlx			mlx;
	t_player		p;
	t_trigo			trigo;
	t_flag			flag;
	t_ray			ray;
	t_map			map;
	t_weapon		weapon;
	struct timeval	last_time;
	struct timeval	last_fps_print;
	float			fps;
	float			delta_time;
	float			fov;
	float			fov_2;
	float			tan_fov;
	float			ray_steps;
	float			projection;
	float			target_fov;
	int				img_size;
}	t_data;

// PARSING FUNCTIONS
int		p_err(const char *msg);
t_map	parse_map(char *file_path);
int		is_map_line(char *line);
int		fill_map(t_map *map, int j, int map_lines_count, char **lines);
int		extract_map_data(char **lines, t_map *map, int map_content_start_index);
void	initialize_map_config_flags(t_map *map);
int		count_lines(char *file_path);
int		is_valid_xpm_path(const char *path);

// MAP VALIDATION
int		validate_player_position(t_map *map);
int		validate_map_walls(t_map *map);
int		validate_map(t_map *map);

// RGB VALIDATION
int		process_f_color(t_map *map, char *value_part);
int		process_c_color(t_map *map, char *value_part);
int		is_valid_rgb_component(char *component);
int		parse_and_validate_rgb(char *rgb_string);
int		assign_rgb_color(int *field, const char *value_str, int *is_set_flag);

// TEXTURE VALIDATION
int		assign_texture_path(char **path, const char *path_value, int *is_set);
int		parse_texture_and_color_paths(char **lines, t_map *map, int *start);
int		process_no_texture(t_map *map, char *value_part);
int		process_so_texture(t_map *map, char *value_part);
int		process_we_texture(t_map *map, char *value_part);
int		process_ea_texture(t_map *map, char *value_part);

//DRAW RAY
void	draw_ray(t_data *game);
t_coord	draw_walls(t_data *g, float wall_distance);

//INIT
t_map	get_map(void);
void	windows_init(t_mlx *mlx, t_data *game);

t_coord	get_player_pos(t_map map);
void	north_orientation(t_player *p);
void	south_orientation(t_player *p);
void	east_orientation(t_player *p);
void	west_orientation(t_player *p);
void	player_init(t_player *player, t_coord pos);

void	init_utils(t_data *game);
void	weapon_init(t_data *game);

//HOOKS
int		released_key(int keycode, t_data *game);
int		pressed_key(int keycode, t_data *game);
int		ft_close(t_data *game);
int		mouse(int x, int y, t_data *game);
//MOVEMENT
void	move_player(t_data *g);
void	offset(t_flag *f, t_player *player, float delta_time);
void	bobbing(t_data *game);
void	move_player_forward(t_data *g, float speed);
void	move_player_backward(t_data *g, float speed);
void	move_player_left(t_data *g, float speed);
void	move_player_right(t_data *g, float speed);
void	validate_move(t_data *g, float new_x, float new_y);
//MINIMAP
void	draw_minimap(t_data *game);
void	draw_square(t_coord co, int size, bool full, t_img *img);
void	draw_triangle_side(t_trigo a, t_trigo perp, t_img *img);
//WEAPON
int		fire(int button, int x, int y, t_data *g);
void	weapon_anim(t_data *game);
//UTILS
void	put_pixel(t_img *img, int x, int y, int color);
void	put_fps(t_data *game);
void	change_fov(t_data *g);
void	draw_xpm(t_data *g, t_img *i, t_coord dst, int scale);
void	ft_exit(int n, char *message, t_map *map);
void	print_error(char *message);
#endif