/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:27 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/04 11:14:09 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floors(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, 0x00FFFFFF);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, 0x0087CEEB);
}

void	draw_floor_and_ceiling(t_vars *var, t_data *mlx)
{
	int y123 = var->lineOff + var->lineH;
	int counter = 0;
	while (y123 < mlx->win_y)
	{
		draw_floors(var->r, y123, mlx);
		draw_ceiling(var->r, mlx->win_y - y123, mlx);
		y123++;
	}
}