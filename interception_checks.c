/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interception_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:15:56 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 18:33:06 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

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

void	switch_var(t_vars *var)
{
	var->vx = var->rx;
	var->vy = var->ry;
	var->dof = 0;
	var->disH = 100000;
	var->Tan = 1.0 / var->Tan;
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

	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if(var->shade == 1)
	{
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


