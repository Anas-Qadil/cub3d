/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_v2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:47:14 by aqadil            #+#    #+#             */
/*   Updated: 2022/07/17 08:38:09 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_2d_init(t_map_vars *var)
{
	var->i = -1;
	var->j = -1;
	var->loopi = 0;
	var->loopj = 0;
	var->savei = 0;
	var->savej = 0;
}

void	init_hooks(t_data *mlx)
{
	mlx->move_up = 0;
	mlx->move_down = 0;
	mlx->move_right = 0;
	mlx->move_left = 0;
}

void	init_cast_vars(t_vars *var, t_data *mlx)
{
	float	calul;

	calul = (float)(mlx->win_x / 1000.0);
	var->rays_num = mlx->win_x;
	var->next_ra = (0.060 / ((calul) + ((calul * 5) / 100)));
	var->color = 0x00e83838;
	var->max_ray_checks = 30;
	var->r = 0;
	var->ra = fix_ang(mlx->pa + 30);
	var->i = 0;
	var->hx = mlx->px;
	var->hy = mlx->py;
}

void	init_map(t_data *mlx)
{
	mlx->square_size = 16;
	mlx->map_s = 64;
	mlx->line_height = mlx->win_y / 2;
}
