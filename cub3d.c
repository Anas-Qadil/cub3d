/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/24 16:23:36 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DR 0.0174533 // one degree in radian
#define PI 3.141
#define P2 PI/2
#define P3  3*PI/2
float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 15, mapX = 11;
t_ray rays[60];

// pikuma calculation and vars

const int TILE_SIZE = 64;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;
const float FOV_ANGLE = 60 * (PI / 180);
const int NUM_RAYS = 60;
const int WALL_STRIP_WIDTH = 1;


int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
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
						my_mlx_pixel_put(mlx, saveI + loopI, saveJ + loopJ, 0x00FFFFFF); // 0x00FF0000 red
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



void	draw_wall(float r, float lineO, float lineH, t_data *mlx)
{
	int i = 0;
	int j = 0;
	int y = 0;
	float ty = 0;
	float  t_step = 64.0 / lineH;
	
	// printf("%f\n", lineH);
	// printf("%f", t_step);
	// exit(0);
	while (i < lineH)
	{
		j = 1;
		int c = mlx->buff[(int)ty * 64];
		int color = c;
		// printf("%d\n", c);
		fflush(stdout);
		while (j < 8)
		{
			my_mlx_pixel_put(mlx, r * 8 - j + 1200, i + lineO, color);
			j++;
		}
		i++;
		ty += t_step;
		printf("%d\n", (int)ty * 64);
	}
	
}



void	draw_floors(float x, float y, t_data *mlx)
{
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 1 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 2 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 3 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 4 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 5 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 6 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 7 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 + 1200, y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 1 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 2 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 3 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 4 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 5 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 6 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 7 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 + 1200, y, 0x0087CEEB);
}

void	draw_wall_textures()
{
	int i = 0;
	int j = 0;
	int i2 = 0;
	int j2 = 0;
	float x = 0;
	float y = 0;
	int width = 200;
	int height = 200;
	int tex_w = 64;
	int tex_h = 64;
	
	float inc_w = 64.0 / 8.0;
	// float inc_h = 64.0 / lineH;
	int m = 0;

	int hi = 0;
	int wi = 0;
	
	while (i < 60)
	{
		// draw_wall(rays[i].r, rays[i].lineO, rays[i].lineH, rays[i].mlx);
		i2 = 0;
		j2 = 0;
		while (i2 < rays[i].lineH)
		{
			int color = rays[i].data->colors[(int)((rays[i].x * 64) / 100)][0];
			my_mlx_pixel_put(rays[i].data, rays[i].r * 8 - j2 + 1200, i2 + rays[i].lineO, color);
			i2++;
		}
		printf("%f | %f\n", rays[i].x / 64.0, rays[i].y / 64.0);
		fflush(stdout);
		i++;
	}
}

void    cast(t_data *mlx, float rayAngle)
{
	int color = 0x00e83838;
	int max_ray_checks = 16;
	int r = 0, mx, my, mp, dof;
	float disT;
	float rx, ry, ra, xo, yo;
	ra = pa - DR * 30.0;  // at first 2D player angle hiya ray angle
	if (ra < 0)
		ra += 2 * PI; // angle between PI and 2PI hna bach nresetiw dakchi
	if (ra > 2 * PI)
		ra -= 2 * PI; // same here
	int i = 0;
	
	while (r < 60) // r num of rays
	{
		// horiz lines
		float disH = 1000000, hx = px, hy = py; // hx and hy homa ray pos x and ray pos y f horz line
		float aTan = -1 / tan(ra); // minimize equaltion that are coming
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
			dof = max_ray_checks;
		}
		while (dof < max_ray_checks)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * mapX + mx;
			
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				hx = rx;
				hy = ry;
				disH = ray_dist(px, py, hx, hy, ra);
				dof = max_ray_checks;
				
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
	
		// vertical lines  || hna gha3 dakchi l chra7t lfo9 9elbo finma kayna chi x dir y
		float disV = 1000000.0, vx = px, vy = py;
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
			dof = max_ray_checks;
		}
		while (dof < max_ray_checks)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				vx = rx;
				vy = ry;
				disV = ray_dist(px, py, vx, vy, ra);
				dof = max_ray_checks;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		float shade = 1;
		if (disV < disH)
		{
			shade = 0.5;
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
		draw_line(px, py, rx, ry, mlx, color); // hna l cast d ray 
		
		float ca = pa - ra;
		if (ca < 0) 
		{
			ca += 2 * PI;
		} 
		if (ca > 2 * PI)
		{
			ca -= 2 * PI;
		}
		
		disT = disT * cos(ca); // fish eye fix
		
		float lineH = (mapS * 320 / disT); // 9edma kebrat deist between camera and wall kaykon lwall sghir
		
		float  ty_step = 64.0 / lineH;
		float ty_off = 0;

		if (lineH > 320)
		{
			ty_off = (lineH - 320) / 4.0;
			lineH = 320;
		}
		
		float lineO = 160 - (lineH / 2); // offset bach yrsem men lfo9 
		
		// draw_wall(r, lineO, lineH, mlx); // hna 3d wall

		// remove this
		
		int y = 0;
		float ty = ty_off * ty_step;
		
		float tx;
		if (shade == 1)
			tx = (int) (rx / 4.0) % 64 ;if (ra > PI) {tx = 63 - tx;}
		else
			tx = (int) (ry / 4.0) % 64 ;if (ra > P2 && ra < P3) {tx = 63 - tx;}
		
		// printf("%f\n", lineH);
		// printf("%f", t_step);
		// exit(0);

		ty += 32;
		while (y < lineH)
		{
			int j = 0; 
			int c = mlx->buff[(int)ty * 64 + (int)(tx)] * shade;
			int color = c;
			while (j < 8)
			{
				my_mlx_pixel_put(mlx, r * 8 - j + 1200, y + lineO, color);
				j++;
			}
			y++;
			ty += ty_step;
			
		}


		//end


		
		rays[i].r = r;
		rays[i].lineH = lineH;
		rays[i].lineO = lineO;
		rays[i].data = mlx;
		rays[i].x = rx;
		rays[i].y = ry;

		//draw floors
		int y123 = lineO + lineH;
		while (y123 < 320)
		{
			draw_floors(r, y123, mlx);
			draw_ceiling(r, 320 - y123, mlx);
			y123++;
		}
		
		
		ra += DR;
		if (ra < 0) 
		{
			ra += 2 * PI;
		} 
		if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}
		r++;
		i++;
	}
	// draw_wall_textures();
}

// cast rays


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
		x = ((x) / 64);
		y = ((int)py) / 64;

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
	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->t_img, 1, 1);
	
	
	return (0);
}

void    draw_everything(t_data *mlx, t_player *player)
{
	int w, h;
	mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wood.xpm", &w, &h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel, &mlx->t_line_length, &mlx->t_endian);
	
	int i = 0;
	int j = 0;
	int k = 0;

	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mlx->colors[i][j] = get_color(mlx, i, j);
			j++;
		}
		i++;
	}
	drawMap2D(mlx);
	draw_player(player);
	px = player->x;
	py = player->y;
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, player->img, player->x, player->y);
	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->t_img, 1, 1);
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

int main(void)
{
	t_data		mlx;
	t_player	player;
	int buffer[64] = {0};
	
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

	
	
	int w, h;
	mlx.t_img = mlx_xpm_file_to_image(mlx.mlx, "./textures/wood.xpm", &w, &h);
	mlx.t_addr = mlx_get_data_addr(mlx.t_img, &mlx.t_bits_per_pixel, &mlx.t_line_length, &mlx.t_endian);
	int i = 0;
	int j = 0;
	int buff[64][64];
	
	// mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.t_img, 100, 100);
	int k = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			buff[i][j] = get_color(&mlx, i, j);
			mlx.buff[k] = get_color(&mlx, i, j);
			j++;
			k++;
		}
		i++;
	}

	// float x = 0;
	// float y = 0;
	// int width = 200;
	// int height = 200;
	// int tex_w = 64;
	// int tex_h = 64;
	
	// float inc_w = 64.0 / 500.0;
	// float inc_h = 64.0 / 500.0;

	// int hi = 0;
	// int wi = 0;
	// i = 0;
	// j = 1;
	// int m = 0;
	// int n = 0;
	// while (i < 64 * 64)
	// {
	// 	mlx_pixel_put(mlx.mlx, mlx.win, m, n, mlx.buff[i]);
	// 	if (i % 64 == 0)
	// 	{
	// 		n = 0;
	// 		m++;
	// 	}
	// 	n++;
	// 	i++;
	// 	printf("%d | %d\n", m, n);
	// 	fflush(stdout);
	// }
	

	draw_everything(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
