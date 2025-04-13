/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:42:57 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/13 04:31:38 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define WIDTH 1280
# define HEIGHT 720
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
# define PROJECTION ((WIDTH / 2) / tan(FOV / 2.0f))
# define X_CENTER WIDTH / 2
# define Y_CENTER HEIGHT / 2
# define MINIMAP_SIZE 160
# define TILES_SIZE 15
# define MINIMAP_RADIUS ((MINIMAP_SIZE + 10) / 2) - 1
# define MINIMAP_CENTER (MINIMAP_SIZE + (TILES_SIZE / 2)) / 2
# define MINIMAP_PLAYER MINIMAP_CENTER + (TILES_SIZE / 2)

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
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
	int		column;
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
	float	jump_offset;
	float	jump_time;
	bool	jump;
	int		map;
}	t_flag;

typedef struct s_trigo
{
	float	cos_a;
	float	sin_a;
}	t_trigo;

typedef struct s_data
{
	t_mlx		mlx;
	t_player	p;
	t_trigo		trigo;
	t_flag		flag;
	t_ray		ray;
	t_map		map;
}	t_data;

void	put_pixel(t_img *img, int x, int y, int color);
void	move_player(t_data *g);
void	draw_ray(t_data *game);
float	distance(t_player player, t_ray r);
int		touch(float x, float y, t_map map);
//INIT
t_map	get_map(void);
void	windows_init(t_mlx *mlx, t_data *game);
void	player_init(t_player *player);
void	init_utils(t_data *game);
//HOOKS
int		released_key(int keycode, t_data *game);
int		pressed_key(int keycode, t_data *game);
int		ft_close(t_data *game);
//MINIMAP
void	draw_minimap(t_data *game);
void	draw_square(t_coord co, int size, bool full, t_img *img);
void	part_triangle(int x, int y, t_img *img);
void	draw_triangle_side(t_trigo a, t_trigo perp, t_img *img);
#endif