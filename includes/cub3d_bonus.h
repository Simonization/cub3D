/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:42:57 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/10 18:53:57 by agoldber         ###   ########.fr       */
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
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define BLOCK_SIZE 64
# define PI 3.14159265359
# define P_SIZE 10
# define FOV (PI / 3)
# define PROJECTION ((WIDTH / 2) / tan(FOV / 2))

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

typedef struct s_data
{
	t_mlx		mlx;
	t_player	player;
	t_ray		ray;
	t_map		map;
}	t_data;

void	put_pixel(t_img *img, int x, int y, int color);
void	move_player(t_player *player, t_map map);
void	draw_ray(t_data *game);
//INIT
t_map	get_map(void);
void	windows_init(t_mlx *mlx, t_data *game);
void	player_init(t_player *player);
//HOOKS
int		released_key(int keycode, t_data *game);
int		pressed_key(int keycode, t_data *game);
int		ft_close(t_data *game);
//MINIMAP
void	draw_map(char **map, t_img *img);
void	draw_player(t_coord co, t_img *img);
#endif