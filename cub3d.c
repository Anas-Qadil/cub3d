/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 07:32:42 by aqadil            #+#    #+#             */
/*   Updated: 2022/07/17 08:55:22 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_door(t_keyvars *var, t_data *mlx)
{
	var->xo = 0;
	if (mlx->pdx < 0)
		var->xo = -25;
	else
		var->xo = 25;
	var->yo = 0;
	if (mlx->pdy < 0)
		var->yo = -25;
	else
		var->yo = 25;
	var->ipx = mlx->px / 64.0;
	var->ipx_add_xo = (mlx->px + var->xo) / 64.0;
	var->ipy = mlx->py / 64.0;
	var->ipy_add_yo = (mlx->py + var->yo) / 64.0;
	if (mlx->world->map[var->ipy_add_yo][var->ipx_add_xo] == DOOR)
	{
		mlx->world->map[var->ipy_add_yo][var->ipx_add_xo] = DOOR_CLOSED;
		mlx->start = 1;
	}
}

void	cast(t_data *mlx, float rayAngle)
{
	t_vars	var;

	rayAngle = 1;
	init_cast_vars(&var, mlx);
	while (var.r < var.rays_num)
	{
		vertical_checks(&var, mlx);
		switch_var(&var);
		horiz_checks(&var, mlx);
		var.shade = 1;
		if (var.dis_v < var.dis_h)
		{
			var.shade = 0.5;
			var.rx = var.vx;
			var.ry = var.vy;
			var.dis_h = var.dis_v;
		}
		line_calculation(&var, mlx); // here
		painting_the_line(&var, mlx);
		draw_floor_and_ceiling(&var, mlx);
		var.ra = fix_ang(var.ra - var.next_ra);
		var.r++;
		var.i++;
	}
}

int	mouse(int x, int y, t_data *mlx)
{
	if (x > mlx->win_x)
	{
		mlx->move_right = 1;
		mlx->move_left = 0;
	}
	else if (x < 0)
	{
		mlx->move_left = 1;
		mlx->move_right = 0;
	}
	else if (x > 0 && y > 0)
	{
		mouse_helper(x, y, mlx);
	}
	return (0);
}

void	mouse_init(t_data *mlx)
{
	mlx->old_mouse_x = 0;
	mlx->old_mouse_y = 0;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;
	mlx->gun_state = 0;
	mlx->gun_start = 0;
	mlx->animation_dur = 0;
	mlx->map_x = mlx->world->sizex;
	mlx->map_y = mlx->world->sizey;
}

int	main(int ac, char **av)
{
	t_data		mlx;

	if (ac != 2)
	{
		printf("Error\n");
		printf("check args!\n");
		exit(1);
	}
	mlx.world = parsing(av[1]);
	mouse_init(&mlx);
	init_everything(&mlx);
	init_sprite_images(&mlx);
	mlx_hook(mlx.win, 17, 0, close_win, &mlx);
	mlx_hook(mlx.win, 2, (1L << 0), close_it, &mlx);
	mlx_hook(mlx.win, 6, 0L, mouse, &mlx);
	mlx_hook(mlx.win, 3, (1L << 1), stop_update, &mlx);
	mlx_loop_hook(mlx.mlx, render, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
