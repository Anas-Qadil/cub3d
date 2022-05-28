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

int cast_w = 953;
int cast_h = 642;


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
	int width = 8;

	while (++i < width)
		my_mlx_pixel_put_cast(mlx, (int)(x * width) - i, y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	int i = -1;
	int width = 8;

	while (++i < width)
		my_mlx_pixel_put_cast(mlx, (int)(x * width) - i, y, 0x0087CEEB);
}


void    cast(t_data *mlx, float rayAngle)
{
	int rays_num = 120;
	int color = 0x00e83838;
	int rayXpos[rays_num];
	int rayYpos[rays_num];
	int playerXpos[rays_num];
	int playerYpos[rays_num];
	int max_ray_checks = 20;
	int r = 0, mx, my, mp, dof;
	float disT;
	float rx, ry, ra, xo, yo, disV, disH, vx, vy;
	ra=FixAng(pa+30);
	int i = 0;
	float hx = px, hy = py;
	while (r < rays_num)
	{
		disV = 1000000;
		float Tan = tan(degToRad(ra));
		dof = 0;
		if(cos(degToRad(ra)) > 0.001) //looking left
		{ 
			rx = (((int)px / 64) * 64)+64;      
			ry = (px - rx) * Tan + py; 
			xo = 64; 
			yo = -xo * Tan;
		}
		else if(cos(degToRad(ra)) < -0.001) //looking right
		{ 
			rx = (((int)px / 64) * 64) -0.0001; 
			ry =(px-rx) * Tan + py; 
			xo = -64; 
			yo = -xo * Tan;
		}
		else 
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
				disV = cos(degToRad(ra)) * (rx-px)-sin(degToRad(ra)) * (ry-py);
				dof = max_ray_checks;
			}
			else 
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		vx = rx; vy = ry;
		
		dof = 0; disH = 100000;
		Tan=1.0 / Tan;
		if (sin(degToRad(ra)) > 0.001) 
		{
			ry = (((int)py / 64) * 64) -0.0001; 
			rx = (py - ry) * Tan + px; 
			yo = -64; 
			xo = -yo * Tan;
		}
		else if (sin(degToRad(ra)) < -0.001) 
		{
			ry = (((int)py / 64) * 64) + 64;      
			rx = (py - ry) * Tan + px; 
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
			mx = (int)(rx) / 64; 
			my = (int)(ry) / 64; 
			mp = my * mapX + mx; 
			if (mp > 0 && mp < mapX * mapY && map[my][mx] == 1)
			{
				dof = max_ray_checks;
				disH=cos(degToRad(ra)) * (rx-px)-sin(degToRad(ra)) * (ry-py);
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
		
		rayXpos[i] = rx / 4;
		rayYpos[i] = ry / 4;
		playerXpos[i] = px / 4;
		playerYpos[i] = py / 4;
		
  		int ca = FixAng(pa - ra); 
		disH = disH * cos(degToRad(ca));
		int lineH = (mapS * 640) / (disH); 
		float ty_step = 64.0 / (float)lineH; 
		float ty_off = 0; 
		if(lineH > 640)
		{ 
			ty_off = (lineH-640) / 2.0; 
			lineH = 640;
		}  //line height and limit
		int lineOff = 320 - (lineH>>1);
		
		int y = 0;
		float ty = ty_off * ty_step;
		
		float tx;
		if(shade == 1){ 
			tx = (int)(rx / 2.0) % 64; 
			if(ra > 180)
				tx = 63 - tx;
		}
  		else        
		{ 
			tx = (int)(ry / 2.0) % 64; 
			if(ra > 90 && ra < 270)
				tx = 63 -  tx;
		}

		
		while (y < lineH)
		{
			int j = 0;
			int c = mlx->buff[((int)(ty) * 64) + (int)(tx)];
			int color = c;
			int width = 8;
			while (j < width)
			{
				my_mlx_pixel_put_cast(mlx, r * width - j , y + lineOff, color);
				j++;
			}
			y++;
			ty += ty_step;
			
		}



		//draw floors and cieling
		int y123 = lineOff + lineH;
		int counter = 0;
		while (y123 < 640)
		{
			draw_floors(r, y123, mlx);
			draw_ceiling(r, 640 - y123, mlx);
			y123++;
		}
		
		ra = FixAng(ra - 0.5);
		r++;
		i++;
	}
	i = 0;
	while (i < rays_num)
	{
		draw_line_cast(playerXpos[i], playerYpos[i], rayXpos[i], rayYpos[i], mlx, color);
		i++;
	}
}

int	close_it(int keycode, t_data *mlx)
{
	int x = px;
	int xo = 0;
	if (pdx < 0) 
		xo = -20; 
	else 
		xo = 20;
	int yo = 0;
	if(pdy < 0) 
		yo = -20;
	else 
		yo = 20;
	int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0, ipx_sub_xo = (px - xo)/ 64.0;
	int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0, ipy_sub_yo = (py - yo) / 64.0;
	
	int y = py;
	if (keycode == left_arrow)
	{
		pa += 0.2 * 30; 
		pa = FixAng(pa); 
		pdx = cos(degToRad(pa)); 
		pdy = -sin(degToRad(pa));
	}
	if (keycode == right_arrow)
	{
		pa -= 0.2*30; 
		pa = FixAng(pa); 
		pdx = cos(degToRad(pa)); 
		pdy = -sin(degToRad(pa));
	}
	if (keycode == top_arrow)
	{
		if (map[ipy][ipx_add_xo] == 0)
			px += pdx * 12;
		if (map[ipy_add_yo][ipx] == 0)
			py += pdy * 12;
			
	}
	if (keycode == bottom_arrow)
	{
		if (map[ipy][ipx_sub_xo] == 0)
			px -= pdx * 12;
		if (map[ipy_sub_yo][ipx] == 0)
			py -= pdy * 12;
			
	}
	// open door
	if (keycode == 49)
	{
		int xo = 0; 
		if (pdx < 0) 
			xo = -25;
		else 
			xo = 25;
		int yo = 0; 
		if (pdy < 0) 
			yo  = -25; 
		else yo = 25;
		int ipx = px / 64.0, ipx_add_xo = (px + xo) / 64.0;
		int ipy = py / 64.0, ipy_add_yo = (py + yo) / 64.0;
		map[ipy_add_yo][ipx_add_xo] = 0;
		drawMap2D(mlx);
	}
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

void	init(t_data *mlx)
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
	
}

int	render(t_data *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_image(mlx->mlx, mlx->cast_img);
	mlx_destroy_image(mlx->mlx, mlx->player_img);
	init(mlx);
	draw_everything(mlx);
	return (1);
}

int main(void)
{
	t_data		mlx;
	t_player	player;
	px = 150;
	py = 600;
	
	playerInit(&player);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 15;
	mlx.mlx = mlx_init();
	mlx.win_x = 945;
	mlx.win_y = 640;
	mlx.win = mlx_new_window(mlx.mlx, 953, 642, "Cub3d");
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
	init(&mlx);
	draw_everything(&mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_hook(mlx.win, 2, 1L<<0, close_it, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}