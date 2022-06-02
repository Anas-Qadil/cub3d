/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 07:32:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 21:43:32 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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



void    cast(t_data *mlx, float rayAngle)
{
	t_vars var;
	init_cast_vars(&var, mlx);

	//remove this
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
		var.ra = FixAng(var.ra - var.next_ra);
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

int main(void)
{
	t_data		mlx;
	t_player	player;

	init_everything(&mlx);
	
	mlx_hook(mlx.win, 2, (1L<<0), close_it, &mlx);
	mlx_hook(mlx.win, 3, (1L<<1), stop_update, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}