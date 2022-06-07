/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interception_v2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:01:52 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 18:11:36 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcule_vertical_interception(t_vars *var, t_data *mlx)
{
	var->disV = 1000000;
	var->Tan = tan(deg_to_rad(var->ra));
	var->dof = 0;
	if (cos(deg_to_rad(var->ra)) > 0)
	{
		var->rx = (((int)mlx->px / 64) * 64) + 64;
		var->ry = (mlx->px - var->rx) * var->Tan + mlx->py;
		var->xo = 64;
		var->yo = -var->xo * var->Tan;
	}
	else if (cos(deg_to_rad(var->ra)) < 0)
	{
		var->rx = (((int)mlx->px / 64) * 64) - 0.0001;
		var->ry = (mlx->px - var->rx) * var->Tan + mlx->py;
		var->xo = -64;
		var->yo = -var->xo * var->Tan;
	}
	else
	{
		var->rx = mlx->px;
		var->ry = mlx->py;
		var->dof = var->max_ray_checks;
	}
}

void	calcule_horz_interception(t_vars *var, t_data *mlx)
{
	if (sin(deg_to_rad(var->ra)) > 0)
	{
		var->ry = (((int)mlx->py / 64) * 64) - 0.0001;
		var->rx = (mlx->py - var->ry) * var->Tan + mlx->px;
		var->yo = -64;
		var->xo = -var->yo * var->Tan;
	}
	else if (sin(deg_to_rad(var->ra)) < 0)
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
}
