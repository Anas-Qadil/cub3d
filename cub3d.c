/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/27 15:33:59 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define DR 0.0174533 // one degree in radian
#define PI 3.141
#define P2 PI/2
#define P3  3*PI/2
float px, py, pdx, pdy, pa = 0;
int mapS = 64, mapY = 15, mapX = 11;
t_ray rays[60];

// pikuma calculation and vars

const int TILE_SIZE = 64;
const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;


int map[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
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
	
	while (i < lineH)
	{
		j = 1;
		int c = mlx->buff[(int)ty * 64];
		int color = c;
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
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 1 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 2 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 3 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 4 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 5 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 6 + 1200, y, 0x00FFFFFF);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 7 + 1200, y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 1 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 2 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 3 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 4 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 5 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 6 + 1200, y, 0x0087CEEB);
	mlx_pixel_put(mlx->mlx, mlx->win, x * 8 - 7 + 1200, y, 0x0087CEEB);
}

void	draw_wall_textures()
{
	int i = 0;
	int j = 0;
	int i2 = 0;
	int j2 = 0;
	
	float inc_w = 64.0 / 8.0;
	int m = 0;

	int hi = 0;
	int wi = 0;
	
	while (i < 60)
	{
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
	int max_ray_checks = 8;
	int r = 0, mx, my, mp, dof;
	float disT;
	float rx, ry, ra, xo, yo, disV, disH, vx, vy;
	ra=FixAng(pa+30);   // at first 2D player angle hiya ray angle
	int i = 0;float hx = px, hy = py;
	
	while (r < 60)
	{
		disV = 1000000;
		dof = 0;
		float Tan=tan(degToRad(ra));
		if(cos(degToRad(ra)) > 0.001) // looking right and kandiro > 0.001 cz cos(pi) = 0 o kanzido ,1 for accuracy cz its not a good idea to compare float to int
		{
			rx = (((int)px / 64) * 64) + 64;
			ry =(px - rx) * Tan + py;
			xo = 64; 
			yo = -xo * Tan;
		}
		else if(cos(degToRad(ra)) < -0.001) // looking left
		{
			rx = (((int)px / 64) * 64) -0.0001;
			ry = (px - rx) * Tan + py;
			xo = -64;
			yo = -xo * Tan;
		}
		else 
		{ 
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < max_ray_checks)
		{
			mx=((int)(rx) / 64); 
			my=((int)(ry) / 64); 
			mp=my * mapX + mx;
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				disV = ray_dist(px, py, rx, ry ,ra);
				dof = max_ray_checks;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;
		dof = 0;
		disH = 100000;
		Tan = 1.0 / Tan;
		if (sin(degToRad(ra)) > 0.001) 
		{
			ry=(((int)py / 64) * 64) -0.0001;
			rx=(py-ry) * Tan + px;
			yo = -64;
			xo = -yo * Tan;
		}
		else if (sin(degToRad(ra)) < -0.001)
		{
			ry=(((int)py / 64) * 64) + 64;            
			rx=(py - ry) * Tan + px; 
			yo = 64;
			xo = -yo * Tan;
		}
		else
		{
			rx = px;
			ry = py;
			dof = max_ray_checks;
		}
		while (dof < max_ray_checks)
		{
			mx=(int)(rx) / 64; 
			my=(int)(ry) / 64; 
			mp=my*mapX+mx; 
			if (mp > 0 && mx < mapX && my < mapY && map[my][mx] == 1)
			{
				dof = max_ray_checks;
				disH = ray_dist(px, py, rx, ry ,ra);
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
			disH = disV;
		}
		
		draw_line(px, py, rx, ry, mlx, color);
  		int ca=FixAng(pa-ra); disH=disH*cos(degToRad(ca));
		int lineH = (mapS*320)/(disH); 
		float ty_step=64.0/(float)lineH; 
		float ty_off=0; 
		if(lineH>320){ ty_off=(lineH-320)/2.0; lineH=320;}
		int lineOff = 160 - (lineH>>1);
		int y = 0;
		float ty = ty_off * ty_step;
		
		float tx;
		if(shade==1){ tx=(int)(rx/2.0)%64; if(ra>180){ tx=63-tx;}}  
  		else        { tx=(int)(ry/2.0)%64; if(ra>90 && ra<270){ tx=63-tx;}}
		  
		while (y < lineH)
		{
			int j = 0;
			int c = mlx->buff[((int)(ty) * 64) + (int)(tx)];
			int color = c;
			while (j < 8)
			{
				my_mlx_pixel_put(mlx, r * 8 - j + 1200, y + lineOff, color);
				j++;
			}
			y++;
			ty += ty_step;
			
		}



		//draw floors
		int y123 = lineOff + lineH;
		while (y123 < 320)
		{
			draw_floors(r, y123, mlx);
			draw_ceiling(r, 320 - y123, mlx);
			y123++;
		}
		
		ra=FixAng(ra-1);  
		r++;
	}
}

int	close_it(int keycode, t_data *mlx)
{
	int x = px;
	int xo = 0;
	if (pdx < 0) {xo = -20;} else {xo = 20;}
	int yo = 0;if(pdy < 0) {yo = -20;} else yo = 20;
	int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo)/ 64.0;
	int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;
	
	int y = py;
	mlx_clear_window(mlx->mlx, mlx->win);
	if (keycode == left_arrow)
	{
		pa+=0.2*15; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
	}
	if (keycode == right_arrow)
	{
		pa-=0.2*15; pa=FixAng(pa); pdx=cos(degToRad(pa)); pdy=-sin(degToRad(pa));
	}
	if (keycode == top_arrow)
	{
		if (map[ipy][ipx_add_xo] == 0)
			px += pdx * 6;
		if (map[ipy_add_yo][ipx] == 0)
			py += pdy * 6;
			
	}
	if (keycode == bottom_arrow)
	{
		if (map[ipy][ipx_sub_xo] == 0)
			px -= pdx * 6;
		if (map[ipy_sub_yo][ipx] == 0)
			py -= pdy * 6;
			
	}
	// open door
	if (keycode == 49)
	{
		int xo = 0; if (pdx < 0) {xo = -25;} else {xo = 25;}
		int yo = 0; if (pdy < 0) {yo  = -25;} else {yo = 25;}
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;
		printf("ipy_add_yo: %d | ipx_add_xo: %d\n", ipy_add_yo, ipx_add_xo);
		// map[ipy_add_yo][ipx_add_xo] = 0;
		// drawMap2D(mlx);
	}

	// render images
	if (keycode != 0)
		close_it(0, mlx);
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player->img, px, py);
	cast(mlx, 0);
	
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->t_img, 1, 1);
	
	
	return (0);
}

void    draw_everything(t_data *mlx, t_player *player)
{
	int w, h;
	mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wall3.xpm", &w, &h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel, &mlx->t_line_length, &mlx->t_endian);

	mlx->img = mlx_new_image(mlx->mlx, 2000, 1000);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
	
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
	mlx.t_img = mlx_xpm_file_to_image(mlx.mlx, "./textures/wall3.xpm", &w, &h);
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
	
	draw_everything(&mlx, &player);
	mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
