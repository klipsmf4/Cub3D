/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klever <klever@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:29:13 by klever            #+#    #+#             */
/*   Updated: 2020/12/27 21:16:26 by klever           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdint.h>
# include "./gnl/get_next_line.h"
# include "./minilibx/mlx.h"

# define MV_UP 13
# define MV_DW 1
# define MV_LF 0
# define MV_RT 2
# define LEFT 123
# define RIGHT 124
# define ESC 53

# define TURN 0.03
# define MOVE 0.025

typedef enum		e_form
{
	nofile = -1, xpm = 0, png = 1
}					t_form;

typedef	enum		e_dir
{
	NONE = -1, N, S, E, W, F, C
}					t_dir;

typedef struct		s_key
{
	unsigned int	key_up;
	unsigned int	key_dw;
	unsigned int	key_lf;
	unsigned int	key_rt;
	unsigned int	key_rotl;
	unsigned int	key_rotr;
}					t_key;

typedef struct		s_rgb
{
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	unsigned char	a;
}					t_rgb;

typedef union		u_colour
{
	unsigned int	colour;
	t_rgb			rgb;
}					t_colour;

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_player
{
	t_pos			pos;
	t_dir			startdir;
	int				quest;
}					t_player;

typedef struct		s_render
{
	t_pos			transform;
	int				screenx;
	t_pos			start;
	double			start0;
	t_pos			end;
	t_pos			dim;
	t_colour		col;
}					t_render;

typedef struct		s_cfloor
{
	t_pos			pos;
	t_pos			fstart;
}					t_cfloor;

typedef struct		s_line
{
	int				height;
	int				start;
	int				end;
}					t_line;

typedef	struct		s_view
{
	int				side;
	double			camera_x;
	double			fsdist;
	double			wallhit;
	t_pos			deltadist;
	t_pos			dir;
	t_pos			plane;
	t_pos			raydir;
	t_pos			raypos;
	t_pos			sidedist;
	t_pos			step;
	t_line			line;
}					t_view;

typedef struct		s_sprite
{
	t_pos			pos;
	double			dist;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_map
{
	char			**data;
	int				cols;
	int				rows;
	int				spritenum;
	int				star;
	double			*perpdist;
	t_sprite		*sprites;
}					t_map;

typedef struct		s_img
{
	void			*ptr;
	char			*addr;
	int				bpp;
	int				linesize;
	int				endian;
	int				width;
	int				height;
	t_pos			t_step;
	t_pos			pos;
}					t_img;

typedef struct		s_config
{
	int				i;
	int				map_found;
	t_img			tex[6];
	t_img			sprite;
	t_colour		floor;
	t_colour		ceiling;
	intmax_t		screenwidth;
	intmax_t		screenheight;
}					t_config;

typedef struct		s_game
{
	void			*mlx_win;
	void			*mlx;
	int				save;
	unsigned short	frame;
	t_img			img;
	t_img			fr1;
	t_img			fr2;
	t_key			keys;
	t_config		config;
	t_map			map;
	t_view			view;
	t_player		player;
}					t_game;

//cub3d
void				init_mlx(t_game *game);

//check.c
int		file_checker(int case_n, void *param);
int		arg_checker(t_game *game, int argc, char **argv);
void	config_checker(t_game *game);

//exit.c
int		exiter(t_game *game, int c);
void	err_handler(t_game *game, char *str);
void	map_cleaner(char **map);
void	tex_cleaner(t_game *game, t_img *tex);
void	sprite_evicter(t_sprite **list);

//utils.c
void	pos_setter(t_pos *pos, double x, double y);
int		whitespaceskip(char *line, int *i);
int		isnumber(char *line, int i);
int		value_finder(char *line, int *i, char exc);
int		inset(char *line, int i);

//utils2.c
int		ft_strcmp(const char *s1, const char *s2);
intmax_t	ft_atoi(char *line, int *i);

//init.c
int		init_game(t_game *game, int save);
void	init_img(t_img *img);
void	init_key(t_key *keys);
void	init_config(t_config *config);
void	init_view(t_view *view);

//map.c
void	init_map(t_map *map);
int		map_maker(t_game *game, char *line, int *i);

//parser.c
int		parser(t_game *game, char *map);
int		data_filler(t_game *game, char *line);
int		fc_filler(t_game *game, char *line, int *i);

//config.c
int		res_setter(t_game *game, char *line, int *i);
int		tex_setter(t_game *game, t_img *tex, char *line, int *i);
char	*pathfinder(char *line, int *i, int len);
void	tex_filer(t_game *game, char *path, t_img *tex);
int		colour_setter(t_game *game, t_colour *element, char *line, int *i);

#endif