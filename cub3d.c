/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 07:32:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 17:06:09 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// void	drawSprite(t_data *mlx)
// {

// 	if (px < mlx->spx + 30 && px > mlx->spx - 30 && py < mlx->spy + 30 && py > mlx->spy - 30 && eat == 0)
// 		eat = 1;
// 	// if (mlx->spx > px) {mlx->spx = mlx->spx - 0.3;}
// 	// if (mlx->spx < px) {mlx->spx = mlx->spx + 0.3;}
// 	// if (mlx->spy > py) {mlx->spy = mlx->spy - 0.3;}
// 	// if (mlx->spy < py) {mlx->spy = mlx->spy + 0.3;}

// 	float	sx = mlx->spx - px;
// 	float	sy = mlx->spy - py;
// 	float	sz = mlx->spz;

// 	float	CS = cos(degToRad(pa)), SN = sin(degToRad(pa));
// 	float a = sy * CS + sx * SN;
// 	float b = sx * CS - sy * SN;
// 	sx = a; sy = b;

// 	sx = (sx * 108.0 / sy) + (120 / 2);
// 	sy = (sz * 108.0 / sy) + (80 / 2);
// 	int i = -1;
// 	int all = 120 * 80 / b;
// 	// sprite attack
// 	while (++i < all)
// 	{
// 		int j = -1;
// 		while (++j < all)
// 			mlx_pixel_put(mlx->mlx, mlx->win, sx * 8 - j, sy * 8 - i, 0x00FF0000);
// 	}
// }

void	drawMap2D_floor(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)	
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00FFFFFF);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	drawMap2D_walls(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
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
	while (++var.i < mlx->mapY)
	{
		var.j = -1;
		var.saveI = 0;
		var.saveJ += var.loopJ;
		var.loopI = 0;
		var.loopJ = 0;
		while (++var.j < mlx->mapX)
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

void	vertical_checks(t_vars *var, t_data *mlx)
{
	var->disV = 1000000;
	var->Tan = tan(degToRad(var->ra));
	var->dof = 0;
	if(cos(degToRad(var->ra)) > 0) //looking right
	{
		var->rx = (((int)mlx->px / 64) * 64) + 64;      
		var->ry = (mlx->px - var->rx) * var->Tan + mlx->py;
		var->xo = 64; 
		var->yo = -var->xo * var->Tan;
	}
	else if(cos(degToRad(var->ra)) < 0) //looking left
	{
		var->rx = (((int)mlx->px / 64) * 64) - 0.0001;
		var->ry =(mlx->px - var->rx) * var->Tan + mlx->py; 
		var->xo = -64;
		var->yo = -var->xo * var->Tan;
	}
	else 
	{
		var->rx = mlx->px;
		var->ry = mlx->py;
		var->dof = var->max_ray_checks;
	}
	while (var->dof < var->max_ray_checks)
	{
		var->mx = (int)(var->rx) / 64;
		var->my = (int)(var->ry) / 64;
			
		var->mp = var->my * mlx->mapX + var->mx;
		if (var->mp > 0 && var->mp < mlx->mapX * mlx->mapY && (map[var->my][var->mx] == 1 || map[var->my][var->mx] == DOOR))
		{
			var->disV = ray_dist(mlx->px, mlx->py, var->rx, var->ry, var->ra);
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

void	horiz_checks(t_vars *var, t_data *mlx)
{
	if (sin(degToRad(var->ra)) > 0) // looking up
	{
		var->ry = (((int)mlx->py / 64) * 64) - 0.0001;
		var->rx = (mlx->py - var->ry) * var->Tan + mlx->px;
		var->yo = -64;
		var->xo = -var->yo * var->Tan;
	}
	else if (sin(degToRad(var->ra)) < 0) // looking down
	{
		var->ry = (((int)mlx->py / 64) * 64) + 64;      
		var->rx = (mlx->py - var->ry) * var->Tan + mlx->px; 
		var->yo = 64; 
		var->xo = -var->yo * var->Tan;
	}
	else
	{
		var->rx = mlx->px;
		var->ry = mlx->py;
		var->dof = var->max_ray_checks;
	}
	while (var->dof < var->max_ray_checks)
	{
		var->mx = (int)(var->rx) / 64; 
		var->my = (int)(var->ry) / 64;
		var->mp = var->my * mlx->mapX + var->mx; 
		if (var->mp > 0 && var->mp < mlx->mapX * mlx->mapY && (map[var->my][var->mx] == 1 || map[var->my][var->mx] == DOOR))
		{
			var->dof = var->max_ray_checks;
			var->disH = ray_dist(mlx->px, mlx->py, var->rx, var->ry, var->ra);
		}
		else
		{
			var->rx += var->xo;
			var->ry += var->yo;
			var->dof += 1;
		}
	}
}

void	init_cast_vars(t_vars *var, t_data *mlx)
{
	var->rays_num = 1000;
	var->color = 0x00e83838;
	var->max_ray_checks = 20;
	var->r = 0;
	var->ra = FixAng(mlx->pa+30);
	var->i = 0;
	var->hx = mlx->px;
	var->hy = mlx->py;
}

void	switch_var(t_vars *var)
{
	var->vx = var->rx; var->vy = var->ry;
	var->dof = 0; var->disH = 100000;
	var->Tan = 1.0 / var->Tan;
}

void	line_calculation(t_vars *var, t_data *mlx)
{
	var->ca = FixAng(mlx->pa - var->ra); // fish eye
	var->disH = var->disH * cos(degToRad(var->ca));
	var->lineH = (mlx->mapS * 640) / (var->disH);
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
	init_cast_vars(&var, mlx);
	int rayXpos[var.rays_num];
	int rayYpos[var.rays_num];
	int playerXpos[var.rays_num];
	int playerYpos[var.rays_num];

	while (var.r < var.rays_num)
	{
		vertical_checks(&var, mlx);
		switch_var(&var);
		horiz_checks(&var, mlx);
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
		playerXpos[var.i] = mlx->px / 4;
		playerYpos[var.i] = mlx->py / 4;
		line_calculation(&var, mlx);
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

void	keycode_init(t_keyvars *var, t_data *mlx)
{
	var->xo = 0;
	if (mlx->pdx < 0)
		var->xo = -20;
	else 
		var->xo = 20;
	var->yo = 0;
	if(mlx->pdy < 0) 
		var->yo = -20;
	else 
		var->yo = 20;
	var->ipx = mlx->px / 64.0, var->ipx_add_xo = (mlx->px + var->xo) / 64.0, var->ipx_sub_xo = (mlx->px - var->xo) / 64.0;
	var->ipy = mlx->py / 64.0, var->ipy_add_yo = (mlx->py + var->yo) / 64.0, var->ipy_sub_yo = (mlx->py - var->yo) / 64.0;
}

void	open_door(t_keyvars *var, t_data *mlx)
{
	var->xo = 0;
	if (mlx->pdx < 0)
		var->xo = -25;
	else 
		var->xo = 25;
	var->yo = 0; 
	if (mlx->pdy < 0) 
		var->yo  = -25; 
	else 
		var->yo = 25;
	var->ipx = mlx->px / 64.0, var->ipx_add_xo = (mlx->px + var->xo) / 64.0;
	var->ipy = mlx->py / 64.0, var->ipy_add_yo = (mlx->py + var->yo) / 64.0;
	if (map[var->ipy_add_yo][var->ipx_add_xo] == DOOR)
		map[var->ipy_add_yo][var->ipx_add_xo] = 0;
}

int	close_it(int keycode, t_data *mlx)
{
	t_keyvars var;
	
	keycode_init(&var, mlx);
	keyhook_1(mlx, &var, keycode);
	if (keycode == D)
		if (map[(int)mlx->py / 64][(int) (mlx->px + 20) / 64] == 0 || map[(int)mlx->py / 64][(int) (mlx->px + 20) / 64] == NORTH)
				mlx->px += 10;
	if (keycode == A)
		if (map[(int)mlx->py / 64][(int) (mlx->px - 20) / 64] == 0 || map[(int)mlx->py / 64][(int) (mlx->px - 20) / 64] == NORTH)
				mlx->px -= 10;
	if (keycode == 49)
		open_door(&var, mlx);
	return (0);
}

void    draw_everything(t_data *mlx)
{
	drawMap2D(mlx);
	draw_player(mlx);

	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img, mlx->px / 4, mlx->py / 4);
}

int	get_player_y_pos(t_data *mlx)
{
	int i = 0;
	int found = 0;
	
	while (i < mlx->mapY)
	{
		int j = 0;
		while (j < mlx->mapX)
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
	
	while (i < mlx->mapY)
	{
		int j = 0;
		while (j < mlx->mapX)
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

void	update_everything(t_data *mlx)
{
	t_keyvars var;

	keycode_init(&var, mlx);
	if (mlx->move_left == 1)
		mlx->pa += 0.2 * 8 * mlx->move_left;
	else
		mlx->pa -= 0.2 * 8 * mlx->move_right;
	mlx->pa = FixAng(mlx->pa);
	mlx->pdx = cos(degToRad(mlx->pa));
	mlx->pdy = -sin(degToRad(mlx->pa));
	if (mlx->move_up == 1)
	{
		if (map[var.ipy][var.ipx_add_xo] == 0 || map[var.ipy][var.ipx_add_xo] == NORTH)
			mlx->px += mlx->pdx * 4 * mlx->move_up;
		if (map[var.ipy_add_yo][var.ipx] == 0 || map[var.ipy_add_yo][var.ipx] == NORTH )
			mlx->py += mlx->pdy * 4 * mlx->move_up;
		mlx->move_down = 0;
	}
	if (mlx->move_down == 1)
	{
		if (map[var.ipy][var.ipx_sub_xo] == 0 || map[var.ipy][var.ipx_sub_xo] == NORTH)
			mlx->px -= mlx->pdx * 4;
		if (map[var.ipy_sub_yo][var.ipx] == 0 || map[var.ipy_sub_yo][var.ipx] == NORTH)
			mlx->py -= mlx->pdy * 4;
		mlx->move_up = 0;
	}
}

int main(void)
{
	t_data		mlx;
	t_player	player;

	// py = get_player_y_pos(&mlx);
	init_everything(&mlx);
	mlx.pa = 90;
	mlx.px = get_player_x_pos(&mlx);;
	mlx.py = get_player_y_pos(&mlx);;
	
	mlx.pdx = cos(degToRad(mlx.pa)); 
	mlx.pdy = -sin(degToRad(mlx.pa));
	
	
	mlx_hook(mlx.win, 2, (1L<<0), close_it, &mlx);
	mlx_hook(mlx.win, 3, (1L<<1), stop_update, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}