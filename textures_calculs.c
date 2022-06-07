/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_calculs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 13:34:52 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:12:14 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_calculs(t_vars *var, t_data *mlx)
{
	var->ca = fix_ang(mlx->pa - var->ra);
	var->disH = var->disH * cos(deg_to_rad(var->ca));
	var->lineH = (mlx->mapS * mlx->win_y) / (var->disH);
	var->ty_step = mlx->door_h / (float)var->lineH;
	var->ty_off = 0;
	if (var->lineH > mlx->win_y)
	{
		var->ty_off = (var->lineH - mlx->win_y) / 2;
		var->lineH = mlx->win_y;
	}
	var->lineOff = (mlx->line_height) - (var->lineH / 2);
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if (var->shade == 1)
	{
		var->tx = (int)(var->rx) % (mlx->door_w);
		if (var->ra > 180)
			var->tx = (mlx->door_w - 1) - var->tx;
	}
	else
	{
		var->tx = (int)(var->ry) % (mlx->door_h);
		if (var->ra > 90 && var->ra < 270)
			var->tx = (mlx->door_w - 1) - var->tx;
	}
}

void	north_calculs(t_vars *var, t_data *mlx)
{
	var->ca = fix_ang(mlx->pa - var->ra);
	var->disH = var->disH * cos(deg_to_rad(var->ca));
	var->lineH = (mlx->mapS * mlx->win_y) / (var->disH);
	var->ty_step = mlx->t_h / (float)var->lineH;
	var->ty_off = 0;
	if (var->lineH > mlx->win_y)
	{
		var->ty_off = (var->lineH - mlx->win_y) / 2;
		var->lineH = mlx->win_y;
	}
	var->lineOff = (mlx->line_height) - (var->lineH / 2);
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if (var->shade == 1)
	{
		var->tx = (int)(var->rx) % (mlx->t_w);
		if (var->ra > 180)
			var->tx = (mlx->t_w - 1) - var->tx;
	}
	else
	{
		var->tx = (int)(var->ry) % (mlx->t_h);
		if (var->ra > 90 && var->ra < 270)
			var->tx = (mlx->t_w - 1) - var->tx;
	}
}

void	south_calculs(t_vars *var, t_data *mlx)
{
	var->ca = fix_ang(mlx->pa - var->ra);
	var->disH = var->disH * cos(deg_to_rad(var->ca));
	var->lineH = (mlx->mapS * mlx->win_y) / (var->disH);
	var->ty_step = mlx->ts_h / (float)var->lineH;
	var->ty_off = 0;
	if (var->lineH > mlx->win_y)
	{
		var->ty_off = (var->lineH - mlx->win_y) / 2;
		var->lineH = mlx->win_y;
	}
	var->lineOff = (mlx->line_height) - (var->lineH / 2);
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if (var->shade == 1)
	{
		var->tx = (int)(var->rx) % (mlx->ts_w);
		if (var->ra > 180)
			var->tx = (mlx->ts_w - 1) - var->tx;
	}
	else
	{
		var->tx = (int)(var->ry) % (mlx->ts_h);
		if (var->ra > 90 && var->ra < 270)
			var->tx = (mlx->ts_w - 1) - var->tx;
	}
}

void	west_calculs(t_vars *var, t_data *mlx)
{
	var->ca = fix_ang(mlx->pa - var->ra);
	var->disH = var->disH * cos(deg_to_rad(var->ca));
	var->lineH = (mlx->mapS * mlx->win_y) / (var->disH);
	var->ty_step = mlx->tw_h / (float)var->lineH;
	var->ty_off = 0;
	if (var->lineH > mlx->win_y)
	{
		var->ty_off = (var->lineH - mlx->win_y) / 2;
		var->lineH = mlx->win_y;
	}
	var->lineOff = (mlx->line_height) - (var->lineH / 2);
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if (var->shade == 1)
	{
		var->tx = (int)(var->rx) % (mlx->tw_w);
		if (var->ra > 180)
			var->tx = (mlx->tw_w - 1) - var->tx;
	}
	else
	{
		var->tx = (int)(var->ry) % (mlx->tw_h);
		if (var->ra > 90 && var->ra < 270)
			var->tx = (mlx->tw_w - 1) - var->tx;
	}
}

void	east_calculs(t_vars *var, t_data *mlx)
{
	var->ca = fix_ang(mlx->pa - var->ra);
	var->disH = var->disH * cos(deg_to_rad(var->ca));
	var->lineH = (mlx->mapS * mlx->win_y) / (var->disH);
	var->ty_step = mlx->te_h / (float)var->lineH;
	var->ty_off = 0;
	if (var->lineH > mlx->win_y)
	{
		var->ty_off = (var->lineH - mlx->win_y) / 2;
		var->lineH = mlx->win_y;
	}
	var->lineOff = (mlx->line_height) - (var->lineH / 2);
	var->y = 0;
	var->ty = var->ty_off * var->ty_step;
	if (var->shade == 1)
	{
		var->tx = (int)(var->rx) % (mlx->te_w);
		if (var->ra > 180)
			var->tx = (mlx->te_w - 1) - var->tx;
	}
	else
	{
		var->tx = (int)(var->ry) % (mlx->te_h);
		if (var->ra > 90 && var->ra < 270)
			var->tx = (mlx->te_w - 1) - var->tx;
	}
}
