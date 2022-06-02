/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_Map2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:30:40 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 17:46:58 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	drawMap2D_floor(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)	
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00FFFFFF);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void	drawMap2D_walls(t_map_vars *var, t_data *mlx)
{
	while (var->loopI < mlx->square_size)
	{
		var->loopJ = 0;
		while (var->loopJ < mlx->square_size)
		{
			if (map[var->i][var->j] == DOOR && var->loopI % 2 == 0)
				my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00000);
			else
				my_mlx_pixel_put(mlx, var->saveI + var->loopI, var->saveJ + var->loopJ, 0x00a9a9a9);
			var->loopJ++;
		}
		var->loopI++;
	}
}

void    drawMap2D(t_data *mlx)
{
	t_map_vars var;

	drawMap2D_init(&var);
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
			if (map[var.i][var.j] == 0 || map[var.i][var.j] == NORTH)
				drawMap2D_floor(&var, mlx);
			else if (map[var.i][var.j] == 1 || map[var.i][var.j] == DOOR)
				drawMap2D_walls(&var, mlx);
		}
	}
}
