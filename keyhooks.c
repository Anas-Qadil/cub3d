/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:33:14 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/03 10:04:23 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

int	stop_update( int keycode, t_data *mlx)
{
	if (keycode == W)
		mlx->move_up = 0;
	if (keycode == S)
		mlx->move_down = 0;
	if (keycode == left_arrow)
		mlx->move_left = 0;
	if (keycode == right_arrow)
		mlx->move_right = 0;
	return (0);
}

void	keyhook_1(t_data *mlx, t_keyvars *var, int keycode)
{
	if (keycode == left_arrow)
	{
		mlx->move_left = 1;
		mlx->move_right = 0;
	}
	if (keycode == right_arrow)
	{
		mlx->move_right = 1;
		mlx->move_left = 0;
	}
	if (keycode == W)
		mlx->move_up = 1;
	if (keycode == S)
		mlx->move_down = 1;
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
	{
		map[var->ipy_add_yo][var->ipx_add_xo] = DOOR_CLOSED;
		mlx->start = 1;
	}	
}

int	close_it(int keycode, t_data *mlx)
{
	t_keyvars var;
	
	keycode_init(&var, mlx);
	keyhook_1(mlx, &var, keycode);
	if (keycode == D && mlx->gameState == GAME)
		if (map[(int)mlx->py / 64][(int) (mlx->px + 20) / 64] == 0 || map[(int)mlx->py / 64][(int) (mlx->px + 20) / 64] == NORTH)
				mlx->px += 10;
	if (keycode == A && mlx->gameState == GAME)
		if (map[(int)mlx->py / 64][(int) (mlx->px - 20) / 64] == 0 || map[(int)mlx->py / 64][(int) (mlx->px - 20) / 64] == NORTH)
				mlx->px -= 10;
	if (keycode == 49 && mlx->gameState == GAME)
		open_door(&var, mlx);
	if (mlx->gameState == HOME_SCREEN && keycode == ENTER_KEY && mlx->isLoadingDone == 1)
	{
		init_player(mlx);
		mlx->gameState = GAME;
	}
	if (mlx->gameState == LOSE && keycode == ENTER_KEY)
	{
		mlx->gameState = HOME_SCREEN;
	}
	return (0);
}