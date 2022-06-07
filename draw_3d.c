/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:12:37 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 15:02:00 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	painting_the_line(t_vars *var, t_data *mlx)
{
	while (var->y < var->lineH)
	{
		if (var->shade == 1)
			handle_east_west(var, mlx);
		else
			handle_north_south(var, mlx);
		my_mlx_pixel_put_cast(mlx, var->r, var->y + var->lineOff, mlx->color);
		var->y++;
		var->ty += (var->ty_step);
	}
}

void	draw_everything(t_data *mlx)
{
	drawMap2D(mlx);
	draw_player(mlx);
	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img,
		mlx->px / 4, mlx->py / 4);
}
