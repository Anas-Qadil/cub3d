/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aqadil <aqadil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 14:16:13 by aqadil            #+#    #+#             */
/*   Updated: 2022/06/02 16:47:32 by aqadil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_data *mlx)
{
	read_textures(mlx);
	create_images(mlx);
}

void	init_vars(t_data *mlx)
{
	mlx->type = 1;
	mlx->state = 1;
	mlx->map = 0;
	mlx->spx = 8 * 64;
	mlx->spy = 4 * 64;
	mlx->spz= 20;
}

void	drawMap2D_init(t_map_vars *var)
{
	var->i = -1;
	var->j = -1;
	var->loopI = 0;
	var->loopJ = 0;
	var->saveI = 0;
	var->saveJ = 0;
}

void   init_hooks(t_data *mlx)
{
	mlx->move_up = 0;
	mlx->move_down = 0;
	mlx->move_right = 0;
	mlx->move_left = 0;
}

void	init_everything(t_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win_x = 953;
	mlx->win_y = 642;
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_x, mlx->win_y, "Cub3d");
	mlx->square_size = 16;
	mlx->mapS = 64;
	mlx->mapY = 11;
	mlx->mapX = 15;
	
	init_hooks(mlx);
	init_vars(mlx);
	init(mlx);
}