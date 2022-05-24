/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:37:04 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/24 11:19:21 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#define left_arrow 123
#define top_arrow 126
#define right_arrow 124
#define bottom_arrow 125


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
	int		buff[10000];
}				t_data;


typedef struct s_point {

	float	x;
	float 	y;
	
}	t_point;

void    draw_square(t_data *mlx, int x);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void    draw_player(t_player *mlx);
int	close_it(int keycode, t_data *mlx);
char	*ft_itoa(int n);
void    draw_player(t_player *mlx);
float	fmodule(float i);
float	ft_abs(float dx, float dy);
void	ft_putchar(char c);
int	close_it(int keycode, t_data *mlx);
void    drawLine(t_ray *ray, int px, int py);
void	my_mlx_pixel_put2(t_player *data, int x, int y, int color);
void	my_mlx_pixel_put3(t_ray *data, int x, int y, int color);

void	draw_ray(int ax, int ay,int bx, int by, t_data *param);

void    draw_everything(t_data *mlx, t_player *player);


// delete thus
void draw_line(float ax, float ay, float bx, float by, t_data *param, int color);
void draw_line_wall(float ax, float ay, float bx, float by, t_data *param, int color);

unsigned int	get_color(t_data *t, int x, int y);

#endif

