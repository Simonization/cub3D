/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:42:57 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/18 03:42:53 by agoldber         ###   ########.fr       */
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
# define P_SIZE 10
# define FOV (PI / 3.0f)
# define FOV_2 (FOV / 2.0f)
# define RAY_STEPS (FOV / WIDTH)
# define PROJECTION ((WIDTH / 2) / tan(FOV / 2.0f))
# define X_CENTER WIDTH / 2
# define Y_CENTER HEIGHT / 2
# define MINIMAP_SIZE 160
# define TILES_SIZE 15
# define MINIMAP_RADIUS ((MINIMAP_SIZE + 10) / 2) - 1
# define MINIMAP_CENTER (MINIMAP_SIZE + (TILES_SIZE / 2)) / 2
# define MINIMAP_PLAYER MINIMAP_CENTER + (TILES_SIZE / 2)
# define VERTICAL 0
# define HORIZONTAL 1
# define CROUCH 102

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <sys/time.h>

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
	int	x;
	int	y;
	int	color;
}	t_coord;

typedef struct s_ray
{
	float	x;
	float	y;
	float	old_x;
	float	old_y;
	float	a;
	float	cos_a;
	float	sin_a;
	bool	v_hit;
	int		col;
	float	wall_height;
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
	bool	run;
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
	float	crouch_offset;
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
	float			ray_steps;
	float			projection;
	float			target_fov;
}	t_data;

//DRAW RAY
void	draw_ray(t_data *game);
float	distance(t_player player, t_ray r, float disto);
int		touch(float x, float y, t_map map);
int		get_light(int color, float wall_distance);
//INIT
t_map	get_map(void);
void	windows_init(t_mlx *mlx, t_data *game);
t_coord	get_player_pos(t_map map);
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
void	delta(float *dx, float *dy, float cos_a, float sin_a);
void	offset(t_flag *f, t_player *player);
void	bobbing(t_data *game);
//MINIMAP
void	draw_minimap(t_data *game);
void	draw_square(t_coord co, int size, bool full, t_img *img);
void	part_triangle(int x, int y, t_img *img);
void	draw_triangle_side(t_trigo a, t_trigo perp, t_img *img);
//WEAPON
int		fire(int button, int x, int y, t_data *g);
void	weapon_anim(t_data *game);
//UTILS
void	put_pixel(t_img *img, int x, int y, int color);
void	put_fps(t_data *game);
void	change_fov(t_data *g);
void	draw_xpm(t_data *g, t_img *i, t_coord dst, int scale);
#endif