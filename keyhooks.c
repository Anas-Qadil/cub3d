/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:33:14 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 20:59:13 by aqadil           ###   ########.fr       */
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
	if (keycode == LEFT_ARROW)
		mlx->move_left = 0;
	if (keycode == right_arrow)
		mlx->move_right = 0;
	if (keycode == A)
		mlx->a_pressed = 0;
	if (keycode == D)
		mlx->d_pressed = 0;
	return (0);
}

void	keyhook_1(t_data *mlx, t_keyvars *var, int keycode)
{
	if (keycode == LEFT_ARROW)
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

void	handle_a_d_moves(t_keyvars *var, t_data *mlx)
{
	var->turn_pdx = cos(deg_to_rad(mlx->pa + 90));
	var->turn_pdy = -sin(deg_to_rad(mlx->pa + 90));
	if (var->turn_pdx < 0)
		var->turn_xo = -20;
	else
		var->turn_xo = 20;
	if (var->turn_pdy < 0)
		var->turn_yo = -20;
	else
		var->turn_yo = 20;
	var->turn_ipx = mlx->px / 64.0;
	var->turn_ipx_add_xo = (mlx->px + var->turn_xo) / 64.0;
	var->turn_ipx_sub_xo = (mlx->px - var->turn_xo) / 64.0;
	var->turn_ipy = mlx->py / 64.0;
	var->turn_ipy_add_yo = (mlx->py + var->turn_yo) / 64.0;
	var->turn_ipy_sub_yo = (mlx->py - var->turn_yo) / 64.0;
}

void	keycode_init(t_keyvars *var, t_data *mlx)
{
	handle_a_d_moves(var, mlx);
	if (mlx->pdx < 0)
		var->xo = -20;
	else
		var->xo = 20;
	var->yo = 0;
	if (mlx->pdy < 0)
		var->yo = -20;
	else
		var->yo = 20;
	var->ipx = mlx->px / 64.0;
	var->ipx_add_xo = (mlx->px + var->xo) / 64.0;
	var->ipx_sub_xo = (mlx->px - var->xo) / 64.0;
	var->ipy = mlx->py / 64.0;
	var->ipy_add_yo = (mlx->py + var->yo) / 64.0;
	var->ipy_sub_yo = (mlx->py - var->yo) / 64.0;
}

int	close_it(int keycode, t_data *mlx)
{
	t_keyvars	var;

	keycode_init(&var, mlx);
	keyhook_1(mlx, &var, keycode);
	if (keycode == D && mlx->game_state == GAME)
		mlx->d_pressed = 1;
	if (keycode == A && mlx->game_state == GAME)
		mlx->a_pressed = 1;
	if (keycode == 49 && mlx->game_state == GAME)
		open_door(&var, mlx);
	if (mlx->game_state == home_SCREEN
		&& keycode == ENTER_KEY && mlx->isloadingdone == 1)
	{
		init_player(mlx);
		mlx->game_state = GAME;
	}
	if (mlx->game_state == lose && keycode == ENTER_KEY)
		mlx->game_state = home_SCREEN;
	if (keycode == EXIT)
		free_and_exit(mlx);
	return (0);
}
