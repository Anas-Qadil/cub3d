/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:37:04 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/10 18:20:29 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define LEFT_ARROW 123
# define TOP_ARROW 126
# define RIGHT_ARROW 124
# define BOTTOM_ARROW 125
# define ENTER_KEY 36
# define DR 0.0174533 // one degree in radian
# define PI 3.141
# define DOOR 126
# define DOOR_CLOSED 621
# define NORTH 100
# define EAST 101
# define SOUTH 102
# define WEST 103
# define W 13
# define S 1
# define D 2
# define A 0
# define HOME_SCREEN 0
# define GAME	1
# define WIN	2
# define LOSE 3
# define EXIT 53
# define SPRT 4321


//parsing

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "./parsing/get_next_line/get_next_line.h"
# define END 1000
# define FLOOR 0
# define WALL 1
// # define WEST 2
// # define SOUTH 3
// # define EAST 4
// # define NORTH 5
// # define DOOR 6
# define SPACES 7
# define NLINE 8
# define ERROR 404

typedef struct s_rgbcolor
{
	char	r[4];
	char	g[4];
	char	b[4];
}	t_rgbcolor;
typedef struct s_mapelements
{
	char		*north_texure;
	char		*south_texure;
	char		*west_texure;
	char		*east_texure;
	t_rgbcolor	*floor_color;
	int			floor_color_;
	t_rgbcolor	ceilling_color;
	int			ceilling_color_;
	int			**map;
	int			*mapone;
	int			sizey;
	int			sizex;
}	t_mapelm;

t_mapelm	*parsing(char *argv);
int			accessingallowed(char *name);
void		checkfilename(char *name);
t_mapelm	*parsingmap(char *name);
int			elementscondictions(char *line);
void		setmapfirsttime(t_mapelm *map);
int			get_elementsvals(char *line, t_mapelm *map, int *x);
char		*ft_strdup(const char *s);
void		north_texure(char *line, t_mapelm *map, int *i);
void		south_texure(char *line, t_mapelm *map, int *i);
void		west_texure(char *line, t_mapelm *map, int *i);
void		east_texure(char *line, t_mapelm *map, int *i);
void		ceilling_color(char *line, t_mapelm *map, int *i);
void		floor_color(char *line, t_mapelm *map, int *i);
int			error(char *line, int ret);
int			ft_isspace(char x);
int			mapandcheck(t_mapelm *map, int fd);
int			ft_isdigit(int c);
void		getrvals_(char *line, t_mapelm *map, int *x);
void		getgvals_(char *line, t_mapelm *map, int *x);
void		getbvals_(char *line, t_mapelm *map, int *x);
void		ceilling_color__(char *line, t_mapelm *map, int *i, int x);
int			ft_atoi(const char *nptr);
void		getrvals(char *line, t_mapelm *map, int *x);
void		getgvals(char *line, t_mapelm *map, int *x);
void		getbvals(char *line, t_mapelm *map, int *x);
void		floor_color__(char *line, t_mapelm *map, int *i, int x);
int			**mapfinal(t_mapelm *map);
int			ft_lenghdoubleint(int **x, int max);
void		demchanging(t_mapelm *map);
int			sizeofit(t_mapelm *map);
int			**freetosavelines(int i, int ***maping, t_mapelm *map);
int			**freetosavelines(int i, int ***maping, t_mapelm *map);
int			nextandperv(t_mapelm *map, int i, int j);
int			wallsurrounding(t_mapelm *map);
int			multipositions(t_mapelm *map);
int			openfile(char *name, t_mapelm *map);
int			mapreadingelements(t_mapelm *map, int fd);
void		freemap(t_mapelm *map);
int			castchartoint(char alpha);
char		*sqpempty(int fd);
int			nomaperror(void);
int			**ft_realocmap(t_mapelm *map, char *line, int i);
int			right_isntwall(t_mapelm *map);
int			leftisntwall(t_mapelm *map);



//end

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// # include "./mlx/mlx.h"
#include <mlx.h>
# include <math.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_player {
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_player;

void    init_sprite_images(t_data *mlx);
void    render_animation(t_data *mlx);

typedef struct s_sprt {
	int		count;
	void	*img[10];
	char	*addr[10];
	int		bits_per_pixel[10];
	int		line_length[10];
	int		endian[10];
	int		buff[10][5000];
	int		h[10];
	int		w[10];
	int		x_pos;
	int		y_pos;
}	t_sprt;

typedef struct s_data {
	t_sprt	sprt;
	t_mapelm *world;
	int		gun_state;
	int		gun_start;
	int		animation_dur;
	void	*img;
	void	*mlx;
	void	*win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		mouse_x;
	int		mouse_y;
	int		old_mouse_x;
	int		old_mouse_y;
	int		x;
	int		y;
	int		win_y;
	int		win_x;
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
	int		square_size;
	int		map_s;
	int		map_y;
	int		map_x;
	float	line_height;
	float	next_ra;
	int		start;
	int		game_state;
	void	*lose_img;
	void	*lose_addr;
	int		lose_bits_per_pixel;
	int		lose_line_length;
	int		lose_endian;
	int		move_left;
	int		move_right;
	int		move_up;
	int		move_down;
	int		a_pressed;
	int		d_pressed;
	void	*home_img;
	void	*home_addr;
	int		home_bits_per_pixel;
	int		home_line_length;
	int		home_endian;
	int		home_w;
	int		home_h;
	int		value;
	int		color;
	void	*press_img;
	void	*press_addr;
	int		press_bits_per_pixel;
	int		press_line_length;
	int		press_endian;
	int		press_w;
	int		press_h;
	void	*loading_img;
	void	*loading_addr;
	int		loading_bits_per_pixel;
	int		loading_line_length;
	int		loading_endian;
	int		loading_i;
	int		loading_j;
	int		loading_counter;
	int		isloadingdone;
	int		loading_w;
	int		loading_h;
	char	*t_path;
	void	*t_img;
	void	*t_addr;
	int		t_bits_per_pixel;
	int		t_line_length;
	int		t_endian;
	int		t_w;
	int		t_h;
	int		*buff;
	char	*ts_path;
	void	*ts_img;
	void	*ts_addr;
	int		ts_bits_per_pixel;
	int		ts_line_length;
	int		ts_endian;
	int		ts_w;
	int		ts_h;
	int		*ts_buff;
	char	*tw_path;
	void	*tw_img;
	void	*tw_addr;
	int		tw_bits_per_pixel;
	int		tw_line_length;
	int		tw_endian;
	int		tw_w;
	int		tw_h;
	int		*tw_buff;
	char	*te_path;
	void	*te_img;
	void	*te_addr;
	int		te_bits_per_pixel;
	int		te_line_length;
	int		te_endian;
	int		te_w;
	int		te_h;
	int		*te_buff;
	char	*door_path;
	void	*door_img;
	void	*door_addr;
	int		door_bits_per_pixel;
	int		door_line_length;
	int		door_endian;
	int		door_w;
	int		door_h;
	int		*door_buff;
	void	*cast_img;
	char	*cast_addr;
	int		cast_bits_per_pixel;
	int		cast_line_length;
	int		cast_endian;
	void	*player_img;
	char	*player_addr;
	int		player_bits_per_pixel;
	int		player_line_length;
	int		player_endian;
	int		type;
	int		state;
	int		map;
	float	spx;
	float	spy;
	float	spz;
	int		sprt_buff2[100000];
}				t_data;

typedef struct s_vars
{
	int		rays_num;
	int		color;
	int		max_ray_checks;
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		dis_t;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dis_v;
	float	dis_h;
	float	vx;
	float	vy;
	int		i;
	float	hx;
	float	hy;
	float	tan;
	int		ca;
	int		line_h;
	float	ty_step;
	float	ty_off;
	float	tx;
	float	ty;
	int		y;
	int		line_offset;
	int		value;
	float	shade;
	float	next_ra;
}	t_vars;

typedef struct s_keyvars{
	int		xo;
	int		yo;
	int		ipx;
	int		ipy;
	int		ipx_add_xo;
	int		ipy_add_yo;
	int		ipx_sub_xo;
	int		ipy_sub_yo;
	float	turn_pdx;
	float	turn_pdy;
	int		turn_xo;
	int		turn_yo;
	int		turn_ipx;
	int		turn_ipy;
	int		turn_ipx_add_xo;
	int		turn_ipy_add_yo;
	int		turn_ipx_sub_xo;
	int		turn_ipy_sub_yo;
}	t_keyvars;

typedef struct s_sprite
{
	int	type;
	int	state;
	int	map;
	int	spx;
	int	spy;
	int	spz;
}	t_sprite;

typedef struct s_map_vars
{
	int	i;
	int	j;
	int	loopi;
	int	loopj;
	int	savei;
	int	savej;
}	t_map_vars;

typedef struct s_point {
	float	x;
	float	y;
}	t_point;

void			draw_square(t_data *mlx, int x);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			draw_player(t_data *mlx);
char			*ft_itoa(int n);
float			fmodule(float i);
void			init_hooks(t_data *mlx);
float			ft_abs(float dx, float dy);
void			ft_putchar(char c);
void			draw_everything(t_data *mlx);
float			deg_to_rad(float a);
float			fix_ang(float a);
void			cast(t_data *mlx, float rayAngle);
void			draw_floors(float x, float y, t_data *mlx);
void			draw_ceiling(float x, float y, t_data *mlx);
void			my_mlx_pixel_put_cast(t_data *data, int x, int y, int color);
void			my_mlx_pixel_put_player(t_data *data, int x, int y, int color);
float			ray_dis_t(float ax, float ay, float bx, float by);
unsigned int	get_color_2(t_data *t, int x, int y);
int				render(t_data *mlx);
void			read_north_texture(t_data *mlx);
void			read_west_texture(t_data *mlx);
void			read_east_texture(t_data *mlx);
void			read_south_texture(t_data *mlx);
unsigned int	get_color(t_data *mlx, int x, int y);
unsigned int	get_color_2(t_data *mlx, int x, int y);
unsigned int	get_color_3(t_data *mlx, int x, int y);
unsigned int	get_color_4(t_data *mlx, int x, int y);
unsigned int	get_color_5(t_data *mlx, int x, int y);
void			read_door_texture(t_data *mlx);
void			create_images(t_data *mlx);
void			init_everything(t_data *mlx);
void			init_vars(t_data *mlx);
void			draw_map_2d_init(t_map_vars *var);
void			init(t_data *mlx);
void			init_cast_vars(t_vars *var, t_data *mlx);
void			init_player(t_data *mlx);
void			init_map(t_data *mlx);
void			init_window(t_data *mlx);
void			init_HOME_SCREEN_vars(t_data *mlxmlx);
void			read_textures(t_data *mlx);
void			door_calculs(t_vars *var, t_data *mlx);
void			north_calculs(t_vars *var, t_data *mlx);
void			south_calculs(t_vars *var, t_data *mlx);
void			west_calculs(t_vars *var, t_data *mlx);
void			east_calculs(t_vars *var, t_data *mlx);
void			update_everything(t_data *mlx);
void			keycode_init(t_keyvars *var, t_data *mlx);
void			nit_hooks(t_data *mlx);
int				stop_update( int keycode, t_data *mlx);
void			keyhook_1(t_data *mlx, t_keyvars *var, int keycode);
int				close_it(int keycode, t_data *mlx);
void			open_door(t_keyvars *var, t_data *mlx);
void			draw_map_2d_floor(t_map_vars *var, t_data *mlx);
void			drawMap2D_walls(t_map_vars *var, t_data *mlx);
void			draw_map_2d(t_data *mlx);
void			draw_floor_and_ceiling(t_vars *var, t_data *mlx);
void			draw_ceiling(float x, float y, t_data *mlx);
void			draw_floors(float x, float y, t_data *mlx);
int				get_player_y_pos(t_data *mlx);
int				get_player_x_pos(t_data *mlx);
void			painting_the_line(t_vars *var, t_data *mlx);
void			vertical_checks(t_vars *var, t_data *mlx);
void			switch_var(t_vars *var);
void			horiz_checks(t_vars *var, t_data *mlx);
void			line_calculation(t_vars *var, t_data *mlx);
void			my_mlx_pixel_put_loading(t_data *data, int x, int y, int color);
void			open_textures(t_data *mlx);
void			draw_loading(t_data *mlx);
void			render_lose_screen(t_data *mlx);
void			check_if_player_is_dead(t_data *mlx);
void			render_HOME_SCREEN(t_data *mlx);
void			free_and_exit(t_data *mlx);
void			init_sprite(t_data *mlx);
void			drawSprite(t_data *mlx);
int				get_player_direction(t_data *mlx);
void			read_home_image(t_data *mlx);


void			handle_north_tx(t_vars *var, t_data *mlx);
void			handle_east_west(t_vars *var, t_data *mlx);
void			handle_east_tx(t_vars *var, t_data *mlx);
void			handle_north_south(t_vars *var, t_data *mlx);

void			calcule_vertical_interception(t_vars *var, t_data *mlx);
void			calcule_horz_interception(t_vars *var, t_data *mlx);
void			handle_a_d_moves(t_keyvars *var, t_data *mlx);
void			update_move_up(t_data *mlx, t_keyvars *var);
int				check_valid_move(t_keyvars *var, int pos);
void			update_move_down(t_data *mlx, t_keyvars *var);
void			update_a_pressed(t_data *mlx, t_keyvars *var);
void			update_d_pressed(t_data *mlx, t_keyvars *var);

#endif