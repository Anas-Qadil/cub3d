/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_Map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:30:40 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 15:14:13 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	draw_map_2d_floor(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			my_mlx_pixel_put(mlx, var->saveI + var->loopI,
				var->saveJ + var->loopJ, 0x00FFFFFF);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	draw_map_2d_walls(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			if (map[var->i][var->j] == DOOR && var->loopI % 2 == 0)
				my_mlx_pixel_put(mlx, var->saveI + var->loopI,
					var->saveJ + var->loopJ, 0x00000);
			else
				my_mlx_pixel_put(mlx, var->saveI + var->loopI,
					var->saveJ + var->loopJ, 0x00a9a9a9);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	draw_map2d_closed_doors(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			if (map[var->i][var->j] == DOOR_CLOSED && var->loopI % 2 == 0)
				my_mlx_pixel_put(mlx, var->saveI + var->loopI,
					var->saveJ + var->loopJ, 0x00808080);
			else
				my_mlx_pixel_put(mlx, var->saveI + var->loopI,
					var->saveJ + var->loopJ, 0x00FFFFFF);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	draw_map_2d(t_data *mlx)
{
	t_map_vars	var;

	draw_map_2d_init(&var);
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
			if (map[var.i][var.j] == 0 || map[var.i][var.j] == NORTH
			|| map[var.i][var.j] == EAST || map[var.i][var.j] == SOUTH
			|| map[var.i][var.j] == WEST)
				draw_map_2d_floor(&var, mlx);
			else if (map[var.i][var.j] == DOOR_CLOSED)
				draw_map2d_closed_doors(&var, mlx);
			else if (map[var.i][var.j] == 1 || map[var.i][var.j] == DOOR)
				draw_map_2d_walls(&var, mlx);
		}
	}
}
