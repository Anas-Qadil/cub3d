/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interception_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:15:56 by aqadil            #+#    #+#             */
/*   Updated: 2022/07/17 08:57:03 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vertical_checks(t_vars *var, t_data *mlx)
{
	calcule_vertical_interception(var, mlx);
	while (var->dof < var->max_ray_checks)
	{
		var->mx = (int)(var->rx) / 64;
		var->my = (int)(var->ry) / 64;
		var->mp = var->my * mlx->map_x + var->mx;
		if (var->mp >= 0 && var->mp < mlx->map_x * mlx->map_y // > 0 => >=0
			&& (mlx->world->map[var->my][var->mx] == 1
			||	mlx->world->map[(int)(var->ry - 1) / 64][(int)(var->rx - 1) / 64] == 1
			||	mlx->world->map[(int)(var->ry + 1) / 64][(int)(var->rx + 1) / 64] == 1
			|| mlx->world->map[var->my][var->mx] == DOOR))
		{
			var->dis_v = ray_dis_t(mlx->px, mlx->py, var->rx, var->ry);
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

void	switch_var(t_vars *var)
{
	var->vx = var->rx;
	var->vy = var->ry;
	var->dof = 0;
	var->dis_h = 10000000;
	var->tan = 1.0 / var->tan;
}

void	horiz_checks(t_vars *var, t_data *mlx)
{
	calcule_horz_interception(var, mlx);
	while (var->dof < var->max_ray_checks)
	{
		var->mx = (int)(var->rx) / 64;
		var->my = (int)(var->ry) / 64;
		var->mp = var->my * mlx->map_x + var->mx;
		if (var->mp > 0 && var->mx >= 0 && var->my >= 0
			&& var->mp < mlx->map_x * mlx->map_y
			&& (mlx->world->map[var->my][var->mx] == 1
			||	mlx->world->map[(int)(var->ry - 1) / 64][(int)(var->rx - 1) / 64] == 1
			||	mlx->world->map[(int)(var->ry + 1) / 64][(int)(var->rx + 1) / 64] == 1
			|| mlx->world->map[var->my][var->mx] == DOOR))
		{
			var->dof = var->max_ray_checks;
			var->dis_h = ray_dis_t(mlx->px, mlx->py, var->rx, var->ry);
		}
		else
		{
			var->rx += var->xo;
			var->ry += var->yo;
			var->dof += 1;
		}
	}
}

void	line_c_door_north(t_vars *var, t_data *mlx)
{
	if ((int)(var->ry / 64) >= mlx->world->sizey || (int)(var->ry / 64) < 0 
		|| (int)(var->rx / 64) >= mlx->world->sizex
		||	(int)(var->rx / 64) < 0)
		{
			north_calculs(var, mlx);
			return ;
		}
	if (var->ra > 0 && var->ra < 180)
	{
		if (mlx->world->map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
			door_calculs(var, mlx);
		else
			south_calculs(var, mlx);
	}
	else
	{
		if (mlx->world->map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
			door_calculs(var, mlx);
		else
			north_calculs(var, mlx);
	}
}

void	line_calculation(t_vars *var, t_data *mlx)
{
	if (var->shade == 1)
		line_c_door_north(var, mlx); // here
	if (var->shade != 1)
	{
		if (var->ra > 90 && var->ra < 270)
		{
			if (mlx->world->map[(int)(var->ry / 64)]
			[(int)(var->rx / 64)] == DOOR)
				door_calculs(var, mlx);
			else
				east_calculs(var, mlx);
		}
		else
		{
			if (mlx->world->map[(int)(var->ry / 64)]
			[(int)(var->rx / 64)] == DOOR)
				door_calculs(var, mlx);
			else
				west_calculs(var, mlx);
		}
	}
}
