/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 17:49:27 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/11 10:21:23 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floors(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, mlx->floor_color);
}

void	draw_ceiling(float x, float y, t_data *mlx)
{
	my_mlx_pixel_put_cast(mlx, (int)(x), (int)y, mlx->cieling_color);
}

void	draw_floor_and_ceiling(t_vars *var, t_data *mlx)
{
	int	y123;
	int	counter;

	y123 = var->line_offset + var->line_h;
	counter = 0;
	while (y123 < mlx->win_y)
	{
		draw_floors(var->r, y123, mlx);
		draw_ceiling(var->r, mlx->win_y - y123, mlx);
		y123++;
	}
}
