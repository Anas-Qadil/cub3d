/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 18:12:37 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/03 15:11:24 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	painting_the_line(t_vars *var, t_data *mlx)
{
	while (var->y < var->lineH)
	{
		int value, color;
		// value = ((int)(var->ty) * mlx->t_w) + (int)(var->tx * (mlx->t_w / 64));
		if (var->shade == 1)
		{
			if (var->ra > 0 && var->ra < 180)
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
				{
					value = ((int)(var->ty) * mlx->door_w) + (int)(var->tx * (mlx->door_w / 64));
					color = mlx->door_buff[value];
				}
				else
				{
					value = ((int)(var->ty) * mlx->t_w) + (int)(var->tx * (mlx->t_w / 64));
					color = mlx->buff[value];
				}
			}
			else
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
				{
					value = ((int)(var->ty) * mlx->door_w) + (int)(var->tx * (mlx->door_w / 64));
					color = mlx->door_buff[value];
				}
				else
				{
					value = ((int)(var->ty) * mlx->ts_w) + (int)(var->tx * (mlx->ts_w / 64));
					color = mlx->ts_buff[value];
				}
			}
		}
		else
		{
			if (var->ra > 90 && var->ra < 270)
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
				{
					value = ((int)(var->ty) * mlx->door_w) + (int)(var->tx * (mlx->door_w / 64));
					color = mlx->door_buff[value];
				}
				else
				{
					value = ((int)(var->ty) * mlx->tw_w) + (int)(var->tx * (mlx->tw_w / 64));
					color = mlx->tw_buff[value];
				}
			}
			else
			{
				if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
				{
					value = ((int)(var->ty) * mlx->door_w) + (int)(var->tx * (mlx->door_w / 64));
					color = mlx->door_buff[value];	
				}
				else
				{
					value = ((int)(var->ty) * mlx->te_w) + (int)(var->tx * (mlx->te_w / 64));
					color = mlx->te_buff[value];
				}
			}
		}
		my_mlx_pixel_put_cast(mlx, var->r, var->y + var->lineOff, color);
		var->y++;
		var->ty += (var->ty_step);
	}
}

void    draw_everything(t_data *mlx)
{
	drawMap2D(mlx);
	draw_player(mlx);

	cast(mlx, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->cast_img, 0, 0);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 1, 1);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->player_img, mlx->px / 4, mlx->py / 4);
}
