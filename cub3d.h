/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:37:04 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/28 16:00:11 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define left_arrow 123
#define top_arrow 126
#define right_arrow 124
#define bottom_arrow 125


// pikuma calculation and vars





#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mlx.h>
#include <math.h>
#include <string.h>

typedef struct	s_data t_data;


typedef struct	s_player {
	void	*img;
    void    *mlx;
    void    *win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     x;
    int     y;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float moveSpeed;
	float rotationSpeed;
}				t_player;

typedef struct s_ray
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     x;
    int     y;
	float 	r;
	int 	lineH;
	int 	lineO;
	t_data  *data;
} t_ray;
t_ray rays[60];

typedef struct	s_data {
	void	*img;
    void    *mlx;
    void    *win;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     x;
    int     y;
    t_player    *player;
	t_ray	*ray;

	int		win_y;
	int 	win_x;

	// textures
	void	*t_img;
	void	*t_addr;
	int		t_bits_per_pixel;
	int		t_line_length;
	int		t_endian;
	int		colors[32][32];
	int		buff[4096];

	// cast 3d
	void	*cast_img;
	char		*cast_addr;
	int		cast_bits_per_pixel;
	int		cast_line_length;
	int		cast_endian;

	// player
	void	*player_img;
	char	*player_addr;
	int		player_bits_per_pixel;
	int		player_line_length;
	int		player_endian;
	
}				t_data;


typedef struct s_point {

	float	x;
	float 	y;
	
}	t_point;

void    draw_square(t_data *mlx, int x);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_player(t_data *mlx);
int	close_it(int keycode, t_data *mlx);
char	*ft_itoa(int n);

float	fmodule(float i);
float	ft_abs(float dx, float dy);
void	ft_putchar(char c);
int	close_it(int keycode, t_data *mlx);
void    drawLine(t_ray *ray, int px, int py);
void	my_mlx_pixel_put2(t_player *data, int x, int y, int color);
void	my_mlx_pixel_put3(t_ray *data, int x, int y, int color);

void	draw_ray(int ax, int ay,int bx, int by, t_data *param);

void    draw_everything(t_data *mlx);


// delete thus
void draw_line(float ax, float ay, float bx, float by, t_data *param, int color);
void draw_line_wall(float ax, float ay, float bx, float by, t_data *param, int color);

unsigned int	get_color(t_data *t, int x, int y);
float degToRad(float a);
float FixAng(float a);
float distance(float ax, float ay, float bx, float by, float ang);
void    cast(t_data *mlx, float rayAngle);
void	draw_floors(float x, float y, t_data *mlx);
void	draw_ceiling(float x, float y, t_data *mlx);
void	my_mlx_pixel_put_cast(t_data *data, int x, int y, int color);

void	my_mlx_pixel_put_player(t_data *data, int x, int y, int color);
void draw_line_cast(float ax, float ay, float bx, float by, t_data *param, int color);

#endif

