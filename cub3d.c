#include "cub3d.h"

#define DR 0.0174533 // one degree in radian
#define PI 3.141
#define P2 PI/2
#define P3  3*PI/2
float px, py, pdx, pdy, pa;
int mapS = 64, mapY = 15, mapX = 11;
t_ray rays[60];

// pikuma calculation and vars

const int TILE_SIZE = 16;

const int square_size = 64;

const int MAP_NUM_ROWS = 11;
const int MAP_NUM_COLS = 15;
const float FOV_ANGLE = 60 * (PI / 180);
const int NUM_RAYS = 60;
const int WALL_STRIP_WIDTH = 1;

int cast_w = 945;
int cast_h = 640;


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
	int saveI = 0, saveJ = 0;
	
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
	float  t_step = (float)square_size / lineH;

	while (i < lineH)
	{
		j = 1;
		int c = mlx->buff[(int)ty * 64];
		int color = c;
		while (j < 8)
		{
			my_mlx_pixel_put(mlx, r * 8 - j + 1200, i + lineO, color);
			j++;
		}
		i++;
		ty += t_step;
	}
	
}



void	draw_floors(float x, float y, t_data *mlx)
{
	int i = -1;
	int width = 16;

	while (++i < width)
		my_mlx_pixel_put_cast(mlx, (int)(x * width) - i, y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	int i = -1;
	int width = 16;

	while (++i < width)
		my_mlx_pixel_put_cast(mlx, (int)(x * width) - i, y, 0x0087CEEB);
}

void    cast(t_data *mlx, float rayAngle)
{
	int rayXpos[60];
	int rayYpos[60];
	int playerXpos[60];
	int playerYpos[60];
	int color = 0x00e83838;
	int max_ray_checks = 10;
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
			ry = (floor((int)py / square_size) * square_size) - 0.0001; // to calculate the first ry intercept on ry : kol square is multiple of 64 kan9semo 3la 64 o kandiro floor bach yhbat lvalue then kandorbo f 64 bach tpushi lvalue
			rx = (py - ry) * aTan + px;  // to calculate the first rx intercept on rx
			yo = -square_size;
			xo = -yo * aTan;
		}
		if (ra < PI) // ila kan ray kaychof lfo9
		{
			ry = (floor((int) py / square_size) * square_size) + square_size; // to calculate the first ry intercept on ry
			rx = (py - ry) * aTan  + px; // to calculate the first rx intercept on rx !!!
			yo = square_size; // to move to the next intercept on yo
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
			mx = (int)(rx) / square_size;
			my = (int)(ry) / square_size;
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
			rx = (((int)px / square_size) * square_size) - 0.0001;
			ry = (px - rx) * nTan + py;
			xo = -square_size;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) {
			rx = (((int) px / square_size) * square_size) + square_size;
			ry = (px - rx) * nTan + py;
			xo = square_size;
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
			mx = (int)(rx) / square_size;
			my = (int)(ry) / square_size;
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
		draw_line_cast(px / 4, py / 4, rx / 4, ry / 4, mlx, color); // hna l cast d ray 
		rayXpos[i] = rx / 4;
		rayYpos[i] = ry / 4;
		playerXpos[i] = px / 4;
		playerYpos[i] = py / 4;
		// my_mlx_pixel_put_cast(mlx, r * width - j, y + lineO, color);
		
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
		
		float lineH = (mapS * 640 / disT); // 9edma kebrat deist between camera and wall kaykon lwall sghir
		
		float  ty_step = (float)square_size / lineH; // 64.0
		float ty_off = 0;

		if (lineH > 640)
		{
			ty_off = (lineH - 640) / 2.0;
			lineH = 640;
		}
		
		float lineO = 320 - (lineH / 2); // offset bach yrsem men lfo9 


		// remove this
		
		int y = 0;
		float ty = ty_off * ty_step;
		
		float tx;
		if (shade == 1)
			tx = (int) (rx / 4.0) % square_size ;if (ra > PI) {tx = square_size - 1 - tx;}
		else
			tx = (int) (ry / 4.0) % square_size ;if (ra > P2 && ra < P3) {tx = square_size - 1 - tx;}
		while (y < lineH)
		{
			int j = 0; 
			// int c = mlx->colors[(int)ty][(int)tx];
			int c = mlx->buff[((int)(ty) * square_size) + (int)(tx)];
			int color = c;
			int width = 16;
			while (j < width)
			{
				my_mlx_pixel_put_cast(mlx, r * width - j, y + lineO, color);
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
		while (y123 < 640)
		{
			draw_floors(r, y123, mlx);
			draw_ceiling(r, 640 - y123, mlx);
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
	draw_player(mlx);
	drawMap2D(mlx);
	// draw rays
	i = 0;
	while (i < 60)
	{
		draw_line_cast(playerXpos[i], playerYpos[i], rayXpos[i], rayYpos[i], mlx, color);
		i++;
	}
}

int	close_it(int keycode, t_data *mlx)
{
	int x = px;
	int xo = 0;
	if (pdx < 0) {xo = -20;} else {xo = 20;}
	int yo = 0;if(pdy < 0) {yo = -20;} else yo = 20;
	int ipx = px / (float)square_size, ipx_add_xo = (px + xo) / (float)square_size, ipx_sub_xo = (px - xo)/ (float)square_size; // 64.0
	int ipy = py / (float)square_size, ipy_add_yo = (py + yo) / (float)square_size, ipy_sub_yo = (py - yo) / (float)square_size; // 64.0
	
	int y = py;
	mlx_clear_window(mlx->mlx, mlx->win);
	if (keycode == left_arrow)
	{
		x = (((x) - pdx) / square_size);
		y = (y - pdy) / square_size;

		mlx->player->turnDirection = -1;
		
		pa -= 0.1;
		if(pa < 0)
			pa += 2 * PI;

		pdx = cos(pa) * 5;
		pdy = sin(pa) * 5;
	}
	if (keycode == right_arrow)
	{
		pa += 0.1 ; 
		if(pa > 2 * PI)
			pa -= 2 * PI;

		pdx = cos(pa) * 5; 
		pdy = sin(pa) * 5;
	}
	if (keycode == top_arrow)
	{
		if (map[ipy][ipx_add_xo] == 0)
			px += pdx;
		if (map[ipy_add_yo][ipx] == 0)
			py += pdy;
			
	}
	if (keycode == bottom_arrow)
	{
		if (map[ipy][ipx_sub_xo] == 0)
			px -= pdx;
		if (map[ipy_sub_yo][ipx] == 0)
			py -= pdy;
			
	}

	// render images
	if (keycode != 0)
		close_it(0, mlx);
	
	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img, px / 4, py / 4);
	return (0);
}

void    draw_everything(t_data *mlx)
{
	drawMap2D(mlx);
	draw_player(mlx);

	// cast(mlx, 0);
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

void	init(t_data *mlx, t_player *player)
{
	int w, h;
	// texture
	mlx->t_img = mlx_xpm_file_to_image(mlx->mlx, "./textures/wall2.xpm", &w, &h);
	mlx->t_addr = mlx_get_data_addr(mlx->t_img, &mlx->t_bits_per_pixel, &mlx->t_line_length, &mlx->t_endian);

	// map img
	mlx->img = mlx_new_image(mlx->mlx, 240, 175);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->line_length,
								&mlx->endian);
	
	// 3d img
	mlx->cast_img = mlx_new_image(mlx->mlx, cast_w, cast_h);
	mlx->cast_addr = mlx_get_data_addr(mlx->cast_img, &mlx->cast_bits_per_pixel, &mlx->cast_line_length,
								&mlx->cast_endian);

	//player
	mlx->player_img = mlx_new_image(mlx->mlx, 5, 5);

    mlx->player_addr = mlx_get_data_addr(mlx->player_img, &mlx->player_bits_per_pixel, &mlx->player_line_length,
								&mlx->player_endian);
	px = 150;
	py = 600;
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
	mlx.win = mlx_new_window(mlx.mlx, 945, 640, "Cub3d");
	player.mlx = mlx.mlx;
	player.win = mlx.win;

	mlx.player = &player;

	
	
	int w, h;
	mlx.t_img = mlx_xpm_file_to_image(mlx.mlx, "./textures/wall2.xpm", &w, &h);
	mlx.t_addr = mlx_get_data_addr(mlx.t_img, &mlx.t_bits_per_pixel, &mlx.t_line_length, &mlx.t_endian);
	int i = 0;
	int j = 0;
	
	int k = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			mlx.buff[k] = get_color(&mlx, i, j);
			j++;
			k++;
		}
		i++;
	}
	init(&mlx, &player);
	draw_everything(&mlx);
	mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}