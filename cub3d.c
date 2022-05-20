/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:36:48 by aqadil            #+#    #+#             */
/*   Updated: 2022/05/20 13:07:50 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	draw_wall(float r, float lineO, float lineH, t_data *mlx)
{
	int color = 0x0038ade8;
	draw_line_wall(r * 8  + 1200, lineO, r * 8 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 1  + 1200, lineO, r * 8 - 1 + 1200, lineH + lineO, mlx, color ); // hna draw d 3d
	// draw_line(r * 8 - 2  + 1200, lineO, r * 8 - 2 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 3  + 1200, lineO, r * 8 - 3 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 4  + 1200, lineO, r * 8 - 4 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 5  + 1200, lineO, r * 8 - 5 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 6  + 1200, lineO, r * 8 - 6 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	// draw_line(r * 8 - 7  + 1200, lineO, r * 8 - 7 + 1200, lineH + lineO, mlx, color); // hna draw d 3d
	int i = 0;
	int w = 1;
	int h = 1;
	int j = 0;
	// while (i < 10)
	// {
		// void *img = mlx_xpm_file_to_image(mlx->mlx , "./textures/wood.xpm", &w, &h);
		// mlx_put_image_to_window(mlx->mlx, mlx->win, img, r * 8  + 1200, lineH + lineO);
		// i++;
	// }
	// draw_line(r * 8 - 8  + 1200, lineO, r * 8 - 8 + 1200, lineH + lineO, mlx); // hna draw d 3d
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
		
		if (lineH > 320)
		{
			lineH = 320;
		}
		
		float lineO = 160 - (lineH / 2); // offset bach yrsem men lfo9 
		// draw_line(r * 8  + 1200, lineO, r * 8 + 1200, lineH + lineO, mlx); // hna draw d 3d
		draw_wall(r, lineO, lineH, mlx);

		//draw floors
		int y = lineO + lineH;
		while (y < 320)
		{
			draw_floors(r, y, mlx);
			draw_ceiling(r, 320 - y, mlx);
			y++;
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
	}

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
