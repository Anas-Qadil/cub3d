/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/18 12:09:21 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// my raycaster calculation and vars

// hoz intersection
/*
	ay = floor(abs((py / 32))) * 32
	ax = px + ((py - ay) / tan(rayangle))

*/

// hoz xstep and ystep
/*
	ystep = TILE_SIZE
	xstep = TILE_SIZE / tan(rayangle);

*/

#define DR 0.0174533 // one degree in radian
#define PI 3.141
#define P2 PI/2
#define P3  3*PI/2
float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 15, mapX = 11;

// pikuma calculation and vars

const int TILE_SIZE = 64;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;
const float FOV_ANGLE = 60 * (PI / 180);
const int NUM_RAYS = 60;
const int WALL_STRIP_WIDTH = 1;
int rays[60];

//ends here

int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void    drawMap2D(t_data *mlx)
{
	int i = 0, j = 0;
	int loopI = 0, loopJ = 0;
	int saveI, saveJ;
	mlx->img = mlx_new_image(mlx->mlx, 2000, 1000);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
	mlx->x = 1;
	mlx->y = 1;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		saveI = 0;
		saveJ += loopJ;
		loopI = 0;
		loopJ = 0;
		while (j < MAP_NUM_COLS)
		{
			saveI += loopI;
			loopI = 0;
			loopJ = 0;
			if (map[i][j] == 0)
			{
				while (loopI < TILE_SIZE)
				{
					loopJ = 0;
					while (loopJ < TILE_SIZE)
					{
						my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00FFFFFF); // 0x00FF0000 red
						loopJ++;
					}
					loopI++;
				}
				// had loop 3la 9bel dak line between squares
				while (loopI < TILE_SIZE + 1)
				{
					loopJ = 0;
					while (loopJ < TILE_SIZE + 1)
					{
						my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00000000);
						loopJ++;
					}
					loopI++;
				}
			}
			else if (map[i][j] == 1)
			{
				while (loopI < TILE_SIZE)
				{
					loopJ = 0;
					while (loopJ < TILE_SIZE)
					{
						my_mlx_pixel_put(mlx, saveI + loopI, saveJ + loopJ, 0x00a9a9a9 );
						loopJ++;
					}
					loopI++;
				}
				while (loopI < TILE_SIZE + 1)
				{
					loopJ = 0;
					while (loopJ < TILE_SIZE + 1)
					{
						my_mlx_pixel_put(mlx, saveI +loopI, saveJ + loopJ, 0x00000000);
						loopJ++;
					}
					loopI++;
				}
			}
			j++;
		}
		i++;
	}
}

float ray_dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void    cast(t_data *mlx, float rayAngle)
{
	int r = 0, mx, my, mp, dof, disT;
	float rx, ry, ra, xo, yo;
	ra = pa ; // - DR * 30;  // at first 2D player angle hiya ray angle
	if (ra < 0)
		ra += 2 * PI; // angle between PI and 2PI hna bach nresetiw dakchi
	if (ra > 2 * PI)
		ra -= 2 * PI; // same here
	int i = 0;
	
	while (r < 60) // r num of rays
	{
		// horiz lines
		float disH = 1000000, hx = px, hy = py; // hx and hy homa ray pos x and ray pos y f horz line
		float aTan = -1 / tan(ra); // see the circle in google to understand
		dof = 0; // to check 8 checks bach mati7ch f infinit loop
		if (ra > PI) // ila kan ray angle lte7t PI or ray kaychof lte7t
		{
			ry = (floor((int)py / 64) * 64) - 0.0001; // to calculate the first ry intercept on ry : kol square is multiple of 64 kan9semo 3la 64 o kandiro floor bach yhbat lvalue then kandorbo f 64 bach tpushi lvalue
			rx = (py - ry) * aTan + px;  // to calculate the first rx intercept on rx
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) // ila kan ray kaychof lfo9
		{
			ry = (floor((int) py / 64) * 64) + 64; // to calculate the first ry intercept on ry
			rx = (py - ry) * aTan  + px; // to calculate the first rx intercept on rx !!!
			yo = 64; // to move to the next intercept on yo
			xo = -yo * aTan; // to move to the next intercept on xo
		}
		if (ra == 0 || ra == PI) // hna ila kan ray angle hiya 0
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * mapX + mx;
			
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				hx = rx;
				hy = ry;
				disH = ray_dist(px, py, hx, hy, ra);
				dof = 8;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	
		// vertical lines  || hna gha3 dakchi l chra7t lfo9 9elbo finma kayna chi x dir y
		float disV = 1000000, vx = px, vy = py;
		dof = 0;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3) 
		{
			rx = (((int)px / 64) * 64) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) {
			rx = (((int) px / 64) * 64) + 64;
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				vx = rx;
				vy = ry;
				disV = ray_dist(px, py, vx, vy, ra);
				dof = 8;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
		}
		else 
		{
			rx = hx;
			ry = hy;
			disT = disH;
		}
		draw_line(px + 10, py, rx, ry, mlx);
		// float lineH = (mapS * 320 / disT); if (lineH > 320) {lineH = 320;}
		// float lineO = 160 - lineH / 2;                       // hna height d kol wall 
		// draw_line(r * 8 + 530, lineO, r*8+530, lineH + lineO, mlx);
		ra+=DR;
		if (ra < 0) 
		{
			ra += 2 * PI;
		} 
		if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}
		r++;
	}


	char *xinterstr = ft_itoa((int)rx / 64);
	char *yinterstr = ft_itoa((int)ry / 64);

	mlx_string_put(mlx->mlx, mlx->win, 1200, 80, 0x00ffffff, "rx: ");
	mlx_string_put(mlx->mlx, mlx->win, 1280, 80, 0x00ffffff, xinterstr);
	mlx_string_put(mlx->mlx, mlx->win, 1200, 120, 0x00ffffff, "ry: ");
	mlx_string_put(mlx->mlx, mlx->win, 1280, 120, 0x00ffffff, yinterstr);
	// mlx_pixel_put(mlx->mlx, mlx->win, (int)rx, (int)ry, 0x00FF0000);
	
}

// cast rays

void    cast_ray(t_data *mlx)
{
	int columnId = 0;
	float rayAngle = mlx->player->rotationAngle - (FOV_ANGLE / 2);
	int i = 0;
	t_ray ray;

	while (i < 1)
	{
		rayAngle += FOV_ANGLE / NUM_RAYS;
		draw_line(px+10, py, (px + 10) + cos(rayAngle) * 60, py + sin(rayAngle) * 60, mlx);
		columnId++;
		i++;
	}
	
}

// end

int	close_it(int keycode, t_data *mlx)
{
	int x = px;
	int y = py;
  
	
	mlx_clear_window(mlx->mlx, mlx->win);
	if (keycode == left_arrow)
	{
		x = (((x) - pdx) / 64);
		y = (y - pdy) / 64;
		
		mlx->player->turnDirection = -1;
		
		pa -= 0.1;
		if(pa < 0)
			pa += 2 * PI;

		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == right_arrow)
	{
		x = (((x + 10) + pdx) / 64);
		y = (y + pdy)/ 64;
		
		mlx->player->turnDirection = 1;

		pa += 0.1 ; 
		if(pa > 2 * PI)
			pa -= 2 * PI;

		pdx = cos(pa) * 5; 
		pdy = sin(pa) * 5;
	}
	if (keycode == top_arrow)
	{
		mlx->player->walkDirection = 1;
		x = (((x + 10) + pdx) / 64);
		y = (y + pdy)/ 64;
		if (map[y][x] == 0)
		{
			px += pdx;
			py+= pdy;
		}
	}
	if (keycode == bottom_arrow)
	{
		mlx->player->walkDirection = -1;
		x = (((x) - pdx) / 64);
		y = (y - pdy) / 64;
		if (map[y][x] == 0)
		{
			px -= pdx; py-= pdy;
		}
	}

	// render images
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
	mlx->player->rotationAngle += mlx->player->turnDirection * mlx->player->rotationSpeed;
	float newLineX =   px + pdx * 30;
	float newLineY = py + pdy * 30;
	// draw_line((px + 10), py, newLineX + 10, newLineY, mlx);
	// cast_ray(mlx);
	cast(mlx, 0);
	
	float rayAngle = pa - (FOV_ANGLE / 2);
	int yinter = (fabs((py / 64)) * 64);
	int xinter = (px + ((py - yinter) / tan(45)));
	// printing yinte and x inter

	char *yinterstr = ft_itoa(yinter);
	char *xinterstr = ft_itoa(xinter);
	mlx_string_put(mlx->mlx, mlx->win, 1200, 1, 0x00ffffff, "xinter: ");
	mlx_string_put(mlx->mlx, mlx->win, 1280, 1, 0x00ffffff, xinterstr);
	mlx_string_put(mlx->mlx, mlx->win, 1200, 40, 0x00ffffff, "yinter: ");
	mlx_string_put(mlx->mlx, mlx->win, 1280, 40, 0x00ffffff, yinterstr);
	
	

	// just printing player infos and walls

	if (map[y][x] == 1)
	{
		char *map_value = ft_itoa(map[y][x]);
		mlx_string_put(mlx->mlx, mlx->win, 1700, 1, 0x00ffffff, "WALL:");
		mlx_string_put(mlx->mlx, mlx->win, 1780, 1, 0x00ffffff, map_value);
	}
	else
		mlx_string_put(mlx->mlx, mlx->win, 1700, 1, 0x00ffffff, "No Wall");

	char *map_x = ft_itoa(x);
	char *map_y = ft_itoa(y);
	mlx_string_put(mlx->mlx, mlx->win, 1870, 1, 0x00ffffff, "X: ");
	mlx_string_put(mlx->mlx, mlx->win, 1890, 1, 0x00ffffff, map_y);
	mlx_string_put(mlx->mlx, mlx->win, 1910, 1, 0x00ffffff, "Y: ");
	mlx_string_put(mlx->mlx, mlx->win, 1930, 1, 0x00ffffff, map_x);
	char *str_px = ft_itoa(px);
	char *str_py = ft_itoa(py);
	mlx_string_put(mlx->mlx, mlx->win, 1800, 50, 0x00ffffff, "px: ");
	mlx_string_put(mlx->mlx, mlx->win, 1850, 50, 0x00ffffff, str_px);
	mlx_string_put(mlx->mlx, mlx->win, 1800, 80, 0x00ffffff, "py: ");
	mlx_string_put(mlx->mlx, mlx->win, 1850, 80, 0x00ffffff, str_py);

	// pdx and pdy;
	char *str_pdx = ft_itoa(pdx);
	char *str_pdy = ft_itoa(pdy);
	mlx_string_put(mlx->mlx, mlx->win, 1800, 120, 0x00ffffff, "px: ");
	mlx_string_put(mlx->mlx, mlx->win, 1850, 120, 0x00ffffff, str_pdx);
	mlx_string_put(mlx->mlx, mlx->win, 1800, 160, 0x00ffffff, "py: ");
	mlx_string_put(mlx->mlx, mlx->win, 1850, 160, 0x00ffffff, str_pdx);
	
	// player direction;
	char *turn = ft_itoa(mlx->player->turnDirection);
	char *walk = ft_itoa(mlx->player->walkDirection);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 120, 0x00ffffff, "turnDirection: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 120, 0x00ffffff, turn);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 160, 0x00ffffff, "walkDirection: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 160, 0x00ffffff, walk);
	
	// ray x and y

	char *ray_x = ft_itoa(px + 10);
	char *ray_y = ft_itoa(py);
	char *new_ray_x = ft_itoa(newLineX);
	char *new_ray_y = ft_itoa(newLineY);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 300, 0x00ffffff, "ray_x: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 300, 0x00ffffff, ray_x);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 360, 0x00ffffff, "ray_y: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 360, 0x00ffffff, ray_y);
	
	mlx_string_put(mlx->mlx, mlx->win, 1500, 400, 0x00ffffff, "new_ray_x: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 400, 0x00ffffff, new_ray_x);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 460, 0x00ffffff, "new_ray_y: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 460, 0x00ffffff, new_ray_y);

	// angle
	char *angle = ft_itoa(pa);
	mlx_string_put(mlx->mlx, mlx->win, 1500, 560, 0x00ffffff, "Angle: ");
	mlx_string_put(mlx->mlx, mlx->win, 1650, 560, 0x00ffffff, angle);
	
	return (0);
}

void    draw_everything(t_data *mlx, t_player *player)
{
	drawMap2D(mlx);
	draw_player(player);
	px = player->x;
	py = player->y;
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, player->img, player->x, player->y);
	cast(mlx, 0);
}

void    playerInit(t_player *player)
{
	player->turnDirection = 0;
	player->walkDirection = 0;
	player->rotationAngle = PI / 2;
	player->moveSpeed = 3.0;
	player->rotationSpeed = 3 * (PI / 180);
}


int main(void)
{
	t_data		mlx;
	t_player	player;
	
	playerInit(&player);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	mlx.mlx = mlx_init();
	mlx.win_x = 2000;
	mlx.win_y = 1000;
	mlx.win = mlx_new_window(mlx.mlx, 2000, 1000, "Cub3d");
	player.mlx = mlx.mlx;
	player.win = mlx.win;

	mlx.player = &player;
	draw_everything(&mlx, &player);
	
	mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
