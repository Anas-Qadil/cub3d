/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 07:32:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 13:36:24 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DR 0.0174533 // one degree in radian
#define PI 3.141
#define P2 PI/2
#define P3  3*PI/2
#define DOOR 126
#define NORTH 13
#define W 13
#define S 1
#define D 2
#define A 0
void	update_everything();

int move_left = 0;
int move_right = 0;
int move_up = 0;
int move_down = 0;
int i = 0;

float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 11, mapX = 15;
t_ray rays[60];

// pikuma calculation and vars

const int TILE_SIZE = 16;

const int square_size = 64;

const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;
const float FOV_ANGLE = 60 * (PI / 180);
const int NUM_RAYS = 60;
const int WALL_STRIP_WIDTH = 1;

int cast_w = 953;
int cast_h = 642;


int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, DOOR, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, DOOR, 1, 1, 0, 1, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, NORTH, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int depth[1000];
int eat = 0;

void	drawSprite(t_data *mlx)
{

	if (px < mlx->spx + 30 && px > mlx->spx - 30 && py < mlx->spy + 30 && py > mlx->spy - 30 && eat == 0)
		eat = 1;
	// if (mlx->spx > px) {mlx->spx = mlx->spx - 0.3;}
	// if (mlx->spx < px) {mlx->spx = mlx->spx + 0.3;}
	// if (mlx->spy > py) {mlx->spy = mlx->spy - 0.3;}
	// if (mlx->spy < py) {mlx->spy = mlx->spy + 0.3;}

	float	sx = mlx->spx - px;
	float	sy = mlx->spy - py;
	float	sz = mlx->spz;

	float	CS = cos(degToRad(pa)), SN = sin(degToRad(pa));
	float a = sy * CS + sx * SN;
	float b = sx * CS - sy * SN;
	sx = a; sy = b;

	sx = (sx * 108.0 / sy) + (120 / 2);
	sy = (sz * 108.0 / sy) + (80 / 2);
	int i = -1;
	int all = 120 * 80 / b;
	// sprite attack
	while (++i < all)
	{
		int j = -1;
		while (++j < all)
			mlx_pixel_put(mlx->mlx, mlx->win, sx * 8 - j, sy * 8 - i, 0x00FF0000);
	}
}

void	drawMap2D_init(t_map_vars *var)
{
	var->i = -1;
	var->j = -1;
	var->loopI = 0;
	var->loopJ = 0;
	var->saveI = 0;
	var->saveJ = 0;
}

void	drawMap2D_floor(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < TILE_SIZE)	
	{
		var->loopJ = 0;
		while (var->loopJ < TILE_SIZE)
		{
			my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00FFFFFF);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	drawMap2D_walls(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < TILE_SIZE)
	{
		var->loopJ = 0;
		while (var->loopJ < TILE_SIZE)
		{
			if (map[var->i][var->j] == DOOR && var->loopI % 2 == 0)
				my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00000);
			else
				my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00a9a9a9);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void    drawMap2D(t_data *mlx)
{
	t_map_vars var;

	drawMap2D_init(&var);
	while (++var.i < MAP_NUM_ROWS)
	{
		var.j = -1;
		var.saveI = 0;
		var.saveJ += var.loopJ;
		var.loopI = 0;
		var.loopJ = 0;
		while (++var.j < MAP_NUM_COLS)
		{
			var.saveI += var.loopI;
			var.loopI = 0;
			if (map[var.i][var.j] == 0 || map[var.i][var.j] == NORTH)
				drawMap2D_floor(&var, mlx);
			else if (map[var.i][var.j] == 1 || map[var.i][var.j] == DOOR)
				drawMap2D_walls(&var, mlx);
		}
	}
}

float ray_dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_floors(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, 0x0087CEEB);
}

void	vertical_checks(t_vars *var)
{
	var->disV = 1000000;
	var->Tan = tan(degToRad(var->ra));
	var->dof = 0;
	if(cos(degToRad(var->ra)) > 0) //looking right
	{
		var->rx = (((int)px / 64) * 64) + 64;      
		var->ry = (px - var->rx) * var->Tan + py;
		var->xo = 64; 
		var->yo = -var->xo * var->Tan;
	}
	else if(cos(degToRad(var->ra)) < 0) //looking left
	{
		var->rx = (((int)px / 64) * 64) - 0.0001;
		var->ry =(px - var->rx) * var->Tan + py; 
		var->xo = -64;
		var->yo = -var->xo * var->Tan;
	}
	else 
	{
		var->rx = px;
		var->ry = py;
		var->dof = var->max_ray_checks;
	}
	while (var->dof < var->max_ray_checks)
	{
		var->mx = (int)(var->rx) / 64;
		var->my = (int)(var->ry) / 64;
			
		var->mp = var->my * mapX + var->mx;
		if (var->mp > 0 && var->mp < mapX * mapY && (map[var->my][var->mx] == 1 || map[var->my][var->mx] == DOOR))
		{
			var->disV = ray_dist(px, py, var->rx, var->ry, var->ra);
			var->dof = var->max_ray_checks;
		}
		else 
		{
			var->rx += var->xo;
			var->ry += var->yo;
			var->dof += 1;
		}
	}
}

void	horiz_checks(t_vars *var)
{
	if (sin(degToRad(var->ra)) > 0) // looking up
		{
			var->ry = (((int)py / 64) * 64) - 0.0001;
			var->rx = (py - var->ry) * var->Tan + px;
			var->yo = -64;
			var->xo = -var->yo * var->Tan;
		}
		else if (sin(degToRad(var->ra)) < 0) // looking down
		{
			var->ry = (((int)py / 64) * 64) + 64;      
			var->rx = (py - var->ry) * var->Tan + px; 
			var->yo = 64; 
			var->xo = -var->yo * var->Tan;
		}
		else
		{
			var->rx = px;
			var->ry = py;
			var->dof = var->max_ray_checks;
		}
		while (var->dof < var->max_ray_checks)
		{
			var->mx = (int)(var->rx) / 64; 
			var->my = (int)(var->ry) / 64;
			var->mp = var->my * mapX + var->mx; 
			if (var->mp > 0 && var->mp < mapX * mapY && (map[var->my][var->mx] == 1 || map[var->my][var->mx] == DOOR))
			{
				var->dof = var->max_ray_checks;
				var->disH = ray_dist(px, py, var->rx, var->ry, var->ra);
			}
			else
			{
				var->rx += var->xo;
				var->ry += var->yo;
				var->dof += 1;
			}
		}
}

void	init_cast_vars(t_vars *var)
{
	var->rays_num = 1000;
	var->color = 0x00e83838;
	var->max_ray_checks = 20;
	var->r = 0;
	var->ra = FixAng(pa+30);
	var->i = 0;
	var->hx = px;
	var->hy = py;
}

void	switch_var(t_vars *var)
{
	var->vx = var->rx; var->vy = var->ry;
	var->dof = 0; var->disH = 100000;
	var->Tan = 1.0 / var->Tan;
}

void	line_calculation(t_vars *var)
{
	var->ca = FixAng(pa - var->ra); // fish eye
	var->disH = var->disH * cos(degToRad(var->ca));
	var->lineH = (mapS * 640) / (var->disH);
	var->ty_step = 64.0 / (float)var->lineH;
	var->ty_off = 0;
	if(var->lineH > 640)
	{
		var->ty_off = (var->lineH - 640) / 2.0;
		var->lineH = 640;
	}  //line height and limit
	var->lineOff = 320 - (var->lineH / 2);
	depth[var->r] = var->disH;
		
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
		
	if(var->shade == 1){ 
		var->tx = (int)(var->rx) % 64; 
		if(var->ra > 180)
			var->tx = 63 - var->tx;
	}
  	else        
	{ 
		var->tx = (int)(var->ry) % 64; 
		if(var->ra > 90 && var->ra < 270)
			var->tx = 63 -  var->tx;
	}
}

void	painting_the_line(t_vars *var, t_data *mlx)
{
	while (var->y < var->lineH)
	{
		int value, color;
		value = ((int)(var->ty) * 64) + (int)(var->tx);
		if (var->shade == 1)
		{
			if (var->ra > 0 && var->ra < 180)
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
					color = mlx->door_buff[value];
				else
					color = mlx->buff[value];
			}
			else
				color = mlx->ts_buff[value];
		}
		else
		{
			if (var->ra > 90 && var->ra < 270)
				color = mlx->tw_buff[value];
			else
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
				color = mlx->door_buff[value];
				else
					color = mlx->te_buff[value];
			}
		}
		my_mlx_pixel_put_cast(mlx, var->r, var->y + var->lineOff, color);
		var->y++;
		var->ty += var->ty_step;
			
	}
}

void	draw_floor_and_ceiling(t_vars *var, t_data *mlx)
{
	int y123 = var->lineOff + var->lineH;
	int counter = 0;
	while (y123 < 640)
	{
		draw_floors(var->r, y123, mlx);
		draw_ceiling(var->r, 640 - y123, mlx);
		y123++;
	}
}

void    cast(t_data *mlx, float rayAngle)
{
	t_vars var;
	init_cast_vars(&var);
	int rayXpos[var.rays_num];
	int rayYpos[var.rays_num];
	int playerXpos[var.rays_num];
	int playerYpos[var.rays_num];

	while (var.r < var.rays_num)
	{
		vertical_checks(&var);
		switch_var(&var);
		horiz_checks(&var);
		var.shade = 1;
		if (var.disV < var.disH)
		{
			var.shade = 0.5;
			var.rx = var.vx;
			var.ry = var.vy;
			var.disH = var.disV;
		}
		
		// remove this
		rayXpos[var.i] = var.rx / 4;
		rayYpos[var.i] = var.ry / 4;
		playerXpos[var.i] = px / 4;
		playerYpos[var.i] = py / 4;
		line_calculation(&var);
  		painting_the_line(&var, mlx);
		draw_floor_and_ceiling(&var, mlx);
		var.ra = FixAng(var.ra - 0.060);
		var.r++;
		var.i++;
	}
	var.i = 0;
	while (var.i < var.rays_num)
	{
		draw_line_cast(playerXpos[var.i], playerYpos[var.i], rayXpos[var.i], rayYpos[var.i], mlx, var.color);
		var.i++;
	}
}

void	keycode_init(t_keyvars *var)
{
	var->xo = 0;
	if (pdx < 0)
		var->xo = -20;
	else 
		var->xo = 20;
	var->yo = 0;
	if(pdy < 0) 
		var->yo = -20;
	else 
		var->yo = 20;
	var->ipx = px / 64.0, var->ipx_add_xo = (px + var->xo) / 64.0, var->ipx_sub_xo = (px - var->xo) / 64.0;
	var->ipy = py / 64.0, var->ipy_add_yo = (py + var->yo) / 64.0, var->ipy_sub_yo = (py - var->yo) / 64.0;
}

void	keyhook_1(t_data *mlx, t_keyvars *var, int keycode)
{
	if (keycode == left_arrow)
	{
		move_left = 1;
		move_right = 0;
	}
	if (keycode == right_arrow)
	{
		move_right = 1;
		move_left = 0;
	}
	if (keycode == W)
	{
		move_up = 1;
		// if (map[var->ipy][var->ipx_add_xo] == 0 || map[var->ipy][var->ipx_add_xo] == NORTH)
		// 	px += pdx * 12;
		// if (map[var->ipy_add_yo][var->ipx] == 0 || map[var->ipy_add_yo][var->ipx] == NORTH )
		// 	py += pdy * 12;
	}
	if (keycode == S)
	{
		// if (map[var->ipy][var->ipx_sub_xo] == 0 || map[var->ipy][var->ipx_sub_xo] == NORTH)
		// 	px -= pdx * 12;
		// if (map[var->ipy_sub_yo][var->ipx] == 0 || map[var->ipy_sub_yo][var->ipx] == NORTH)
		// 	py -= pdy * 12;
		move_down = 1;
	}
}

void	open_door(t_keyvars *var)
{
	var->xo = 0;
	if (pdx < 0)
		var->xo = -25;
	else 
		var->xo = 25;
	var->yo = 0; 
	if (pdy < 0) 
		var->yo  = -25; 
	else 
		var->yo = 25;
	var->ipx = px / 64.0, var->ipx_add_xo = (px + var->xo) / 64.0;
	var->ipy = py / 64.0, var->ipy_add_yo = (py + var->yo) / 64.0;
	if (map[var->ipy_add_yo][var->ipx_add_xo] == DOOR)
		map[var->ipy_add_yo][var->ipx_add_xo] = 0;
}

int	close_it(int keycode, t_data *mlx)
{
	t_keyvars var;
	
	keycode_init(&var);
	keyhook_1(mlx, &var, keycode);
	if (keycode == D)
		if (map[(int)py / 64][(int) (px + 20) / 64] == 0 || map[(int)py / 64][(int) (px + 20) / 64] == NORTH)
				px += 10;
	if (keycode == A)
		if (map[(int)py / 64][(int) (px - 20) / 64] == 0 || map[(int)py / 64][(int) (px - 20) / 64] == NORTH)
				px -= 10;
	if (keycode == 49)
		open_door(&var);
	return (0);
}

void    draw_everything(t_data *mlx)
{
	drawMap2D(mlx);
	draw_player(mlx);

	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img, px / 4, py / 4);
}

void    playerInit(t_player *player)
{
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->rotationAngle = PI / 2;
	player->moveSpeed = 3.0;
	player->rotationSpeed = 3 * (PI / 180);
}

unsigned int	get_color(t_data *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * t->t_line_length + x * 4;
	ptr = t->t_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

unsigned int	get_color_2(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->tw_line_length + x * 4;
	ptr = mlx->tw_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}
unsigned int	get_color_3(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->te_line_length + x * 4;
	ptr = mlx->te_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}
unsigned int	get_color_4(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->ts_line_length + x * 4;
	ptr = mlx->ts_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}
unsigned int	get_color_5(t_data *mlx, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * mlx->door_line_length + x * 4;
	ptr = mlx->door_addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}

void	init(t_data *mlx)
{
	int w, h;
	 
	// texture North <--
	mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/redbrick.xpm", &w, &h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel, &mlx->t_line_length, &mlx->t_endian);
	int i = 0;
	int k = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->buff[k] = get_color(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

	// texture West <--
	mlx->tw_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wall2.xpm", &w, &h);
	mlx->tw_addr = mlx_get_data_addr(mlx->tw_img, &mlx->tw_bits_per_pixel, &mlx->tw_line_length, &mlx->tw_endian);
	 i = 0;
	 k = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->tw_buff[k] = get_color_2(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

	// // texture East -->
	mlx->te_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/EA.xpm", &w, &h);
	mlx->te_addr = mlx_get_data_addr(mlx->te_img, &mlx->te_bits_per_pixel, &mlx->te_line_length, &mlx->te_endian);
	i = 0;
	k = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->te_buff[k] = get_color_3(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

	// // texture South
	mlx->ts_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/bluestone.xpm", &w, &h);
	mlx->ts_addr = mlx_get_data_addr(mlx->ts_img, &mlx->ts_bits_per_pixel, &mlx->ts_line_length, &mlx->ts_endian);
	i = 0;
	k = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->ts_buff[k] = get_color_4(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

	//door
	mlx->door_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/door.xpm", &w, &h);
	mlx->door_addr = mlx_get_data_addr(mlx->door_img, &mlx->door_bits_per_pixel, &mlx->door_line_length, &mlx->door_endian);
	i = 0;
	k = 0;
	while (i < 64)
	{
		int j = 0;
		while (j < 64)
		{
			mlx->door_buff[k] = get_color_5(mlx, j, i);
			j++;
			k++;
		}
		i++;
	}

	// map img
	mlx->img = mlx_new_image(mlx->mlx, 240, 175);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
	
	// 3d img
	mlx->cast_img = mlx_new_image(mlx->mlx, 2000, 1000);
	mlx->cast_addr = mlx_get_data_addr(mlx->cast_img, &mlx->cast_bits_per_pixel, &mlx->cast_line_length,
								&mlx->cast_endian);

	//player
	mlx->player_img = mlx_new_image(mlx->mlx, 5, 5);

    mlx->player_addr = mlx_get_data_addr(mlx->player_img, &mlx->player_bits_per_pixel, &mlx->player_line_length,
								&mlx->player_endian);
}

int	render(t_data *mlx)
{
	// mlx_clear_window(mlx->mlx, mlx->win);
	update_everything();
	draw_everything(mlx);

	return (1);
}

void	read_animation(t_data *mlx)
{
	int i = 0;
	int w, h;

	// while (i < 12)
	// {
		mlx->sprt_img[0] = mlx_xpm_file_to_image(mlx->mlx, "./textures/soul_0.xpm", &w, &h);
		mlx->sprt_addr[0] = mlx_get_data_addr(mlx->sprt_img[0], &mlx->sprt_bits_per_pixel[0], &mlx->sprt_line_length[0], &mlx->sprt_endian[0]);

		mlx->sprt_img[1] = mlx_xpm_file_to_image(mlx->mlx, "./textures/soul_1.xpm", &w, &h);
		mlx->sprt_addr[1] = mlx_get_data_addr(mlx->sprt_img[1], &mlx->sprt_bits_per_pixel[1], &mlx->sprt_line_length[1], &mlx->sprt_endian[1]);

		mlx->sprt_img[2] = mlx_xpm_file_to_image(mlx->mlx, "./textures/soul_2.xpm", &w, &h);
		mlx->sprt_addr[2] = mlx_get_data_addr(mlx->sprt_img[2], &mlx->sprt_bits_per_pixel[2], &mlx->sprt_line_length[2], &mlx->sprt_endian[2]);

		mlx->sprt_img[3] = mlx_xpm_file_to_image(mlx->mlx, "./textures/soul_3.xpm", &w, &h);
		mlx->sprt_addr[3] = mlx_get_data_addr(mlx->sprt_img[3], &mlx->sprt_bits_per_pixel[3], &mlx->sprt_line_length[3], &mlx->sprt_endian[3]);

		mlx->sprt_img[4] = mlx_xpm_file_to_image(mlx->mlx, "./textures/soul_4.xpm", &w, &h);
		mlx->sprt_addr[4] = mlx_get_data_addr(mlx->sprt_img[4], &mlx->sprt_bits_per_pixel[4], &mlx->sprt_line_length[4], &mlx->sprt_endian[4]);
	// 	i++;
	// }
}

void	init_vars(t_data *mlx)
{
	mlx->type = 1;
	mlx->state = 1;
	mlx->map = 0;
	mlx->spx = 8 * 64;
	mlx->spy = 4 * 64;
	mlx->spz= 20;
}

int	get_player_y_pos(t_data *mlx)
{
	int i = 0;
	int found = 0;
	
	while (i < mapY)
	{
		int j = 0;
		while (j < mapX)
		{
			if (map[i][j] == NORTH)
			{
				found = i;
				break ;
			}
			j++;
		}
		if (found != 0)
			break;
		i++;
	}
	return ((found * 64) + 20);	
}

int	get_player_x_pos(t_data *mlx)
{
	int i = 0;
	int found = 0;
	
	while (i < mapY)
	{
		int j = 0;
		while (j < mapX)
		{
			if (map[i][j] == NORTH)
			{
				found = j;
				break ;
			}
			j++;
		}
		if (found != 0)
			break;
		i++;
	}
	return ((found * 64) + 20);	
}

void	update_everything()
{
	t_keyvars var;

	keycode_init(&var);
	if (move_left == 1)
		pa += 0.2 * 8 * move_left;
	else
		pa -= 0.2 * 8 * move_right;
	pa = FixAng(pa);
	pdx = cos(degToRad(pa));
	pdy = -sin(degToRad(pa));
	if (move_up == 1)
	{
		if (map[var.ipy][var.ipx_add_xo] == 0 || map[var.ipy][var.ipx_add_xo] == NORTH)
			px += pdx * 4 * move_up;
		if (map[var.ipy_add_yo][var.ipx] == 0 || map[var.ipy_add_yo][var.ipx] == NORTH )
			py += pdy * 4 * move_up;
		move_down = 0;
	}
	if (move_down == 1)
	{
		if (map[var.ipy][var.ipx_sub_xo] == 0 || map[var.ipy][var.ipx_sub_xo] == NORTH)
			px -= pdx * 4;
		if (map[var.ipy_sub_yo][var.ipx] == 0 || map[var.ipy_sub_yo][var.ipx] == NORTH)
			py -= pdy * 4;
		move_up = 0;
	}
}

int	stop_update( int keycode, t_data *mlx)
{
	printf("%d\n", keycode);
	fflush(stdout);
	if (keycode == W)
		move_up = 0;
	if (keycode == S)
		move_down = 0;
	if (keycode == left_arrow)
		move_left = 0;
	if (keycode == right_arrow)
		move_right = 0;
	return (0);
}

int main(void)
{
	t_data		mlx;
	t_player	player;

	px = get_player_x_pos(&mlx);
	py = get_player_y_pos(&mlx);
	pa = 90;
	
	playerInit(&player);
	pdx = cos(degToRad(pa)); 
	pdy = -sin(degToRad(pa));
	mlx.mlx = mlx_init();
	mlx.win_x = 953;
	mlx.win_y = 642;
	mlx.win = mlx_new_window(mlx.mlx, 1000, 640, "Cub3d");
	player.mlx = mlx.mlx;
	player.win = mlx.win;

	mlx.player = &player;

	
	
	int w, h;
	int time = 100000;
	
	
	int i = 0;
	int j = 0;
	
	int k = 0;
	init(&mlx);
	init_vars(&mlx);
	draw_everything(&mlx);
	// drawSprite(&mlx);
	// read_animation(&mlx);
	mlx_hook(mlx.win, 2, (1L<<0), close_it, &mlx);
	mlx_hook(mlx.win, 3, (1L<<1), stop_update, &mlx);
	
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}