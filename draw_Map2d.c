/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_Map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:30:40 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/11 10:48:12 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	draw_map_2d_floor(t_map_vars *var, t_data *mlx)
{
	while (var->loopi < mlx->square_size)
	{
		var->loopj = 0;
		while (var->loopj < mlx->square_size)
		{
			my_mlx_pixel_put_cast(mlx, var->savei + var->loopi,
				var->savej + var->loopj, 0x00333333);
			var->loopj++;
		}
		var->loopi++;
	}
}

void	draw_map_2d_walls(t_map_vars *var, t_data *mlx)
{
	while (var->loopi < mlx->square_size)
	{
		var->loopj = 0;
		while (var->loopj < mlx->square_size)
		{
			if (mlx->world->map[var->i][var->j] == DOOR && var->loopi % 2 == 0)
				my_mlx_pixel_put_cast(mlx, var->savei + var->loopi,
					var->savej + var->loopj, 0x00000);
			var->loopj++;
		}
		var->loopi++;
	}
}

void	draw_map2d_closed_doors(t_map_vars *var, t_data *mlx)
{
	while (var->loopi < mlx->square_size)
	{
		var->loopj = 0;
		while (var->loopj < mlx->square_size)
		{
			if (mlx->world->map[var->i][var->j] == DOOR_CLOSED && var->loopi % 2 == 0)
				my_mlx_pixel_put(mlx, var->savei + var->loopi,
					var->savej + var->loopj, 0x00FFFFFF);
			else
				my_mlx_pixel_put(mlx, var->savei + var->loopi,
					var->savej + var->loopj, 0x00FFFFFF);
			var->loopj++;
		}
		var->loopi++;
	}
}

void	draw_map_2d(t_data *mlx)
{
	t_map_vars	var;

	draw_map_2d_init(&var);
	
	while (++var.i < mlx->map_y)
	{
		var.j = -1;
		var.savei = 0;
		var.savej += var.loopj;
		var.loopi = 0;
		var.loopj = 0;
		while (++var.j < mlx->map_x)
		{
			var.savei += var.loopi;
			var.loopi = 0;
			if (mlx->world->map[var.i][var.j] == 0 || mlx->world->map[var.i][var.j] == NORTH
			|| mlx->world->map[var.i][var.j] == EAST || mlx->world->map[var.i][var.j] == SOUTH
			|| mlx->world->map[var.i][var.j] == WEST)
				draw_map_2d_floor(&var, mlx);
			else if (mlx->world->map[var.i][var.j] == DOOR_CLOSED)
				draw_map2d_closed_doors(&var, mlx);
			else if (mlx->world->map[var.i][var.j] == 1 || mlx->world->map[var.i][var.j] == DOOR)
				draw_map_2d_walls(&var, mlx);
		}
	}
}
