/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:01:44 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/07 15:03:57 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int map[11][15];

void	handle_north_tx(t_vars *var, t_data *mlx)
{
	if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
	{
		mlx->value = ((int)(var->ty) * mlx->door_w)
			+ (int)(var->tx * (mlx->door_w / 64));
		mlx->color = mlx->door_buff[mlx->value];
	}
	else
	{
		mlx->value = ((int)(var->ty) * mlx->ts_w)
			+ (int)(var->tx * (mlx->ts_w / 64));
		mlx->color = mlx->ts_buff[mlx->value];
	}
}

void	handle_east_west(t_vars *var, t_data *mlx)
{
	if (var->ra > 0 && var->ra < 180)
		handle_north_tx(var, mlx);
	else
	{
		if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
		{
			mlx->value = ((int)(var->ty) * mlx->door_w)
				+ (int)(var->tx * (mlx->door_w / 64));
			mlx->color = mlx->door_buff[mlx->value];
		}
		else
		{
			mlx->value = ((int)(var->ty) * mlx->t_w)
				+ (int)(var->tx * (mlx->t_w / 64));
			mlx->color = mlx->buff[mlx->value];
		}
	}
}

void	handle_east_tx(t_vars *var, t_data *mlx)
{
	if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
	{
		mlx->value = ((int)(var->ty) * mlx->door_w)
			+ (int)(var->tx * (mlx->door_w / 64));
		mlx->color = mlx->door_buff[mlx->value];
	}
	else
	{
		mlx->value = ((int)(var->ty) * mlx->te_w)
			+ (int)(var->tx * (mlx->te_w / 64));
		mlx->color = mlx->te_buff[mlx->value];
	}
}

void	handle_north_south(t_vars *var, t_data *mlx)
{
	if (var->ra > 90 && var->ra < 270)
		handle_east_tx(var, mlx);
	else
	{
		if (map[(int)(var->ry / 64)][(int)(var->rx / 64)] == DOOR)
		{
			mlx->value = ((int)(var->ty) * mlx->door_w)
				+ (int)(var->tx * (mlx->door_w / 64));
			mlx->color = mlx->door_buff[mlx->value];
		}
		else
		{
			mlx->value = ((int)(var->ty) * mlx->tw_w)
				+ (int)(var->tx * (mlx->tw_w / 64));
			mlx->color = mlx->tw_buff[mlx->value];
		}
	}
}
