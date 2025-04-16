/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:44:12 by agoldber          #+#    #+#             */
/*   Updated: 2025/04/17 00:20:09 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define PI 3.14159265359f
# define P_SIZE 10
# define FOV (PI / 3.0f)
# define PROJECTION ((WIDTH / 2) / tan(FOV / 2.0f))
# define SPEED 5

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
	t_mlx		mlx;
	t_player	player;
	t_trigo		trigo;
	t_ray		ray;
	t_map		map;
}	t_data;

// Parser structures
typedef struct s_parse
{
	int			r1;
	int			r2;
	t_coord		sizemap;
}	t_parse;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	**map;
	char	*filename;
	int		fd;
	int		r1;
	int		r2;
	int		rgbfloor[3];
	int		rgbceiling[3];
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*spritepwd;
	
	double	player_x;
	double	player_y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	
	int		*texture;
	int		*texture2;
	int		*texture3;
	int		*texture4;
	int		*sprite;
	int		texwidth;
	int		texheight;
	int		mapx;
	int		mapy;
	int		maptofree;
	int		mapboleen;
	int		bmp;
	int		textnum;
	int		initsuccess;
	int		errorbool;
	int		numberofplayer;
}	t_display;

void	move_player(t_data *g);
void	draw_ray(t_data *game);
float	distance(t_player player, t_ray r);
int		touch(float x, float y, t_map map);
//INIT
t_map	get_map(void);
void	windows_init(t_mlx *mlx, t_data *game);
void	player_init(t_player *player);
void	init_trigo(t_data *game);
//HOOKS
int		released_key(int keycode, t_data *game);
int		pressed_key(int keycode, t_data *game);
int		ft_close(t_data *game);
//UTILS
void	delta(float *dx, float *dy, float cos_a, float sin_a);
void	put_pixel(t_img *img, int x, int y, int color);

// Parser functions
int		init_parser(t_display *display);
int		parse(int argc, char *str, t_parse *parse, t_display *display);
int		checkparse(t_display *display, t_parse *parse, int fd);
int		parseline(char *line, t_parse *parse, t_display *display);
int		stockmap(t_parse *parse, t_display *display);
int		floodandfill(t_display *display, int mapy, int mapx);
int		checkthewall(t_display *display);
int		checkaround(int mapx, int mapy, t_display *display);
int		checkifgood(char c);
int		checkifgood2(char c);
int		stockcolorf(char *line, t_display *display);
int		stockcolorc(char *line, t_display *display);
int		stockresolution(char *line, t_parse *parse, t_display *display);
int		stocktextures_no(char *line, t_display *display);
int		stocktextures_so(char *line, t_display *display);
int		stocktextures_we(char *line, t_display *display);
int		stocktextures_ea(char *line, t_display *display);
int		stocktextures_s(char *line, t_display *display);
int		showerror(t_display *display, char *str);
int		freemap(t_display *display);
unsigned int colortoint(unsigned int r, unsigned int g, unsigned int b);
int		cmp(char *s1, char *s2, size_t n);
int		checkcubextension(char *str, t_display *display);
int		strlentoend(char *str);
int		isend(char *line);
int		numberblank(char *str);
int		searchcomma(char *line);
int		gotomap(t_display *display, t_parse *parse, int len, int fd);
void	getxy2(t_parse *parse, int b, char *line, int fd);
void	getxymap(t_parse *parse, char *filename);
int		sortmap(t_parse *parse, char *line, int len, t_display *display);
int		mallocmap(t_parse *parse, t_display *display);
char	initposplayer(char pos, int x, int y, t_display *display);

#endif